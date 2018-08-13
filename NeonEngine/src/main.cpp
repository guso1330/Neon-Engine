#include "./app/window.h"
#include "./core/platform/opengl/opengl.h"
#include "./graphics/cameras/camera.h"
#include "./app/input/eventManager.h"
#include "./app/input/input.h"
#include "./utils/debugging/debug.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include <glm/glm.hpp>

using namespace neon;
using namespace glm;

const int WIDTH = 512,
		  HEIGHT = 256;

int main() {

	srand (time(NULL));

	//
	// GLFW is initialized within the window
	// GLAD/OpenGL initialized inside the OpenGL  
	//
	Window *window = new Window(WIDTH, HEIGHT, false, "Neon Engine");
	OpenGLContext* gl_context = new OpenGLContext();
	Input* inputManager = window->GetInput();

	//
	// Initialize the camera
	//
	float aspect_ratio = (float)WIDTH / (float)HEIGHT;
	float fov = 70.0f;
	float near = 0.1f;
	float far = 1000.0f;

	Camera camera(glm::vec3(0, 5.0f, -10.0f), fov, aspect_ratio, near, far);
	float camera_rotate_speed = (M_PI/180) * 0.8;
	
	//
	// Timer variables
	//
	double elapsed_time;
	elapsed_time = 0;
	double last_time = glfwGetTime(), current_time = 0;

	//
	// Camera Variables
	//
	float camera_speed = 0.0f;
	float camera_acceleration = 0.8f;
	float camera_speed_limit = 2.0f;

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

	// Todo: Test a callback that passes a variable to manipulate a variable
	inputManager->BindEvent("CameraMoveAround", NEON_CURSOR_EVENT, Callback<>(MoveCameraAroundFunc));

	//
	// OpenGL Setting
	//
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_CULL_FACE);
	glClearDepth(1.0f);
	glEnable(GL_MULTISAMPLE);

	/**************************
	** MAIN APPLICATION LOOP **
	***************************/
	while (!window->isClosed()) {
		debug::calcFPS(window->GetGLFWwindow(), 1.0, "Neon Engine - Current FPS: ");
		gl_context->Clear();

		// Update timer
		current_time = glfwGetTime();
		elapsed_time = current_time - last_time;

		

		//
		// Handle Camera Updates
		//
		MoveCameraFunc();
		camera.Update();

		window->Update();

		last_time = current_time;
	}

	return EXIT_SUCCESS;
}