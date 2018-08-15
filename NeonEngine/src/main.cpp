#include "./app/window.h"
#include "./core/platform/opengl/opengl.h"
#include "./graphics/cameras/camera.h"
#include "./app/input/eventManager.h"
#include "./app/input/input.h"
#include "./utils/debugging/debug.h"
#include "./core/platform/opengl/shader.h"
#include "./core/platform/opengl/program.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include <glm/glm.hpp>

using namespace neon;
using namespace glm;

const int WIDTH = 512,
		  HEIGHT = 264;

const float cube_vertices[] = {
	// front
	-0.5, -0.5,  0.5,
	 0.5, -0.5,  0.5,
	 0.5,  0.5,  0.5,
	-0.5,  0.5,  0.5,
	// back
	-0.5, -0.5, -0.5,
	 0.5, -0.5, -0.5,
	 0.5,  0.5, -0.5,
	-0.5,  0.5, -0.5,
};

const unsigned int cube_elements[] = {
	// front
	0, 1, 2,
	2, 3, 0,
	// right
	1, 5, 6,
	6, 2, 1,
	// back
	7, 6, 5,
	5, 4, 7,
	// left
	4, 0, 3,
	3, 7, 4,
	// bottom
	4, 5, 1,
	1, 0, 4,
	// top
	3, 2, 6,
	6, 7, 3,
};

int main() {

	srand (time(NULL));

	//
	// GLFW is initialized within the window
	// GLAD/OpenGL initialized inside the OpenGL  
	//
	Window *window = new Window(WIDTH, HEIGHT, false, "Neon Engine");
	OpenGLContext gl_context;
	Input* inputManager = window->GetInput();

	// Create the VAO for cube 
	BufferLayout cube_layout;
	cube_layout.Push(VALUE_TYPE::FLOAT, 3, 0);
	unsigned int cube_vao = gl_context.CreateVao(cube_vertices, 3 * 8 * sizeof(float), cube_elements, 36, cube_layout, VertexBuffer::BufferUsage::STATIC);

	// Create the shaders and the program
	const unsigned int shaders[2] = {
		gl_context.CreateShader("./NeonEngine/src/res/shaders/basicVShader.glsl", GL_VERTEX_SHADER),
		gl_context.CreateShader("./NeonEngine/src/res/shaders/basicFShader.glsl", GL_FRAGMENT_SHADER)
	};

	unsigned int program_id = gl_context.CreateProgram(shaders, 2);
	Program* program = gl_context.GetProgram(program_id);

	program->Bind();
	program->SetUniform4f("vcolor", glm::vec4(1.0f, 0.0, 0.0, 1.0f));

	//
	// Initialize the camera
	//
	float aspect_ratio = (float)WIDTH / (float)HEIGHT;
	float fov = 90.0f;
	float near = 0.1f;
	float far = 1000.0f;

	Camera camera(glm::vec3(0.0, 0.0f, -5.0f), fov, aspect_ratio, near, far);
	
	//
	// Timer variables
	//
	double elapsed_time = 0,
		   last_time = glfwGetTime(),
		   current_time = 0;

	//
	// Camera Variables
	//
	float camera_speed = 0.0f;
	float camera_acceleration = 0.3f;
	float camera_speed_limit = 2.0f;
	float camera_rotate_speed = (M_PI / 180.0f) * 0.5;

	//
	// Input Callback Functions
	//
	auto MoveCameraFunc = [&window, &camera, inputManager, &elapsed_time, &camera_speed, camera_acceleration, camera_speed_limit]() {

		glm::vec3 position = camera.GetPosition();

		camera_speed = camera_speed + (camera_acceleration * elapsed_time);

		// On Key up set camera_speed to 0
		if(inputManager->IsKeyUp(GLFW_KEY_A) && inputManager->IsKeyUp(GLFW_KEY_D) && inputManager->IsKeyUp(GLFW_KEY_W) && inputManager->IsKeyUp(GLFW_KEY_S)) {
			camera_speed = 0.0f;
		}

		// Limit Camera Speed
		if (camera_speed > camera_speed_limit) {
			camera_speed = camera_speed_limit;
		}

		if(inputManager->IsKeyDown(GLFW_KEY_W) || inputManager->IsKeyDown(GLFW_KEY_S)) {
			float lx = glm::sin(camera.GetYaw())*glm::cos(camera.GetPitch());
			float ly = glm::sin(camera.GetPitch());
			float lz = glm::cos(camera.GetYaw())*glm::cos(camera.GetPitch());

			if(inputManager->IsKeyDown(GLFW_KEY_S)) {
				position.x = position.x + (-camera_speed*lx);
				position.y = position.y + (-camera_speed*ly);
				position.z = position.z + (-camera_speed*lz);
			} else {
				position.x = position.x + camera_speed*lx;
				position.y = position.y + camera_speed*ly;
				position.z = position.z + camera_speed*lz;
			}
		}

		if(inputManager->IsKeyDown(GLFW_KEY_A) || inputManager->IsKeyDown(GLFW_KEY_D)) {
			if(inputManager->IsKeyDown(GLFW_KEY_A)) {				
				position += glm::cross(camera.GetRelativeUp(), camera.GetDirection()) * camera_speed;
				
			} else {
				position += glm::cross(camera.GetRelativeUp(), camera.GetDirection()) * -camera_speed;
			}
		}

		camera.SetPosition(position);
	};

	auto MoveCameraAroundFunc = [inputManager, &camera, camera_rotate_speed, &window]() {

		int x = inputManager->GetCursorPosition().x,
			y = inputManager->GetCursorPosition().y;

		int dx = x - WIDTH/2,
			dy = y - HEIGHT/2;

		if(dx) { // get rotation in the x direction
			camera.RotateYaw(-camera_rotate_speed * dx);
		}
		if(dy) {
			camera.RotatePitch(-camera_rotate_speed * dy);
		}

		glfwSetCursorPos(window->GetGLFWwindow(), WIDTH/2, HEIGHT/2);
	};

	// Disable the cursor
	glfwSetCursorPos(window->GetGLFWwindow(), WIDTH/2, HEIGHT/2);
	glfwSetInputMode(window->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Todo: Test a callback that passes a variable to manipulate a variable
	inputManager->BindEvent("CameraMoveAround", NEON_CURSOR_EVENT, Callback<>(MoveCameraAroundFunc));

	float angle = 0.0f,
		  speed = 2.0f;

	glm::mat4 model_matrix(1.0f);
	/**************************
	** MAIN APPLICATION LOOP **
	***************************/
	while (!window->isClosed()) {
		debug::calcFPS(window->GetGLFWwindow(), 1.0, "Neon Engine - Current FPS: ");
		gl_context.Clear();

		// Update timer
		current_time = glfwGetTime();
		elapsed_time = current_time - last_time;

		angle += (elapsed_time * speed);
		if (angle > 360.0) {
			angle = 0;
		}

		model_matrix = glm::mat4(1.0);
		model_matrix = model_matrix * glm::rotate(angle, glm::vec3(0.0, 1.0f, 0.0));

		//
		// Handle Camera Updates
		//
		MoveCameraFunc();
		camera.Update();

		// Set Up simple program
		program->SetUniformMat4("model", model_matrix);
		program->SetUniformMat4("view_projection", camera.GetViewProjection());

		gl_context.Draw(cube_vao, 36, GL_TRIANGLES);

		window->Update();

		last_time = current_time;
	}

	return EXIT_SUCCESS;
}