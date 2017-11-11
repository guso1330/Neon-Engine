#include "./app/window.h"
#include "./shaders/shader.h"
#include "./shaders/program.h"
#include "./graphics/buffers/vertexBuffer.h"
#include "./graphics/buffers/indexBuffer.h"
#include "./graphics/buffers/vertexArray.h"
#include "./graphics/cameras/camera.h"
#include "./graphics/entities/model.h"
#include "./graphics/entities/gameobject.h"
#include "./utils/obj_loader/objloader.h"
#include "./utils/debugging/printing_functions.cpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include <glm/glm.hpp>

using namespace neon;
using namespace glm;

const GLint WIDTH = 1024,
			HEIGHT = 768;

short int CUBE_COL = 50,
		  CUBE_ROW = 50;

short int CUBE_COUNT = CUBE_COL * CUBE_ROW;

int main() {
	srand (time(NULL));
	float rand_color_r, rand_color_g, rand_color_b;

	//
	// Initialize the camera
	//
	float ASPECT_RATIO = (float)WIDTH / (float)HEIGHT;
	float FOV = 70.0f;
	float g_NEAR = 0.1f;
	float g_FAR = 1000.0f;

	Camera camera(glm::vec3(0, 250.0f, -400.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	// Camera camera(glm::vec3(0, 25.0f, -50.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	camera.SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 view_projection = camera.GetViewProjection();
	glm::mat4 model = glm::mat4(1.0f);

	/* GLFW is initialized within the window */
	Window *window = new Window(WIDTH, HEIGHT, false, "Neon Engine");
	window->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/************************************
		Setting up Shaders and Program
		------------------------------
		Need to create an application
		class that has the capability
		of attaching shaders to it
	*************************************/
#if _WIN32
	Shader *vShader = new Shader("../NeonEngine/src/res/shaders/textureVShader.glsl", GL_VERTEX_SHADER);
	Shader *fShader = new Shader("../NeonEngine/src/res/shaders/textureFShader.glsl", GL_FRAGMENT_SHADER);
#elif __APPLE__
	Shader *vShader = new Shader("./NeonEngine/src/res/shaders/textureVShader.glsl", GL_VERTEX_SHADER);
	Shader *fShader = new Shader("./NeonEngine/src/res/shaders/textureFShader.glsl", GL_FRAGMENT_SHADER);
#endif

	std::vector<Shader*> shaders;
	shaders.push_back(vShader);
	shaders.push_back(fShader);
	std::vector<Model*> models;
	Program *program = new Program(shaders);

	program->SetUniformMat4("view_projection", view_projection);
	
	/***************************
		Setting up The Models
	****************************/
#if _WIN32
	std::vector<GameObject*> cubes;
	Model cube("../NeonEngine/src/res/models/cube_5unit.obj", program);

	Model plane("../NeonEngine/src/res/models/plane_5unit.obj", program);
	plane.SetTexture("../NeonEngine/src/res/textures/cartoon_floor_texture.jpg");
#elif __APPLE__

	std::vector<GameObject*> cubes;
	Model cube("./NeonEngine/src/res/models/cube_5unit.obj", program);

	Model plane("./NeonEngine/src/res/models/plane_5unit.obj", program);
	plane.SetTexture("./NeonEngine/src/res/textures/cartoon_floor_texture.jpg");

#endif
	/**********************************/
	
#if _WIN32
	Texture tex("../NeonEngine/src/res/textures/checker.png");
#elif __APPLE__
	Texture tex("./NeonEngine/src/res/textures/checker.png");
#endif
	cube.SetTexture(tex);

	// Build Cubes
	for(int i=0; i < CUBE_COUNT; ++i) {
		#if _WIN32
			cubes.push_back(new GameObject(&cube));
		#elif __APPLE__
			cubes.push_back(new GameObject(&cube));
		#endif
	}

	// Set cube rotation, color, and position
	glm::vec3 square_pos = glm::vec3(245.0f, 0.5f, 245.0f);
	for(int i=0; i<CUBE_COL; ++i) {
		for(int j=0; j < CUBE_COL; ++j) {
			rand_color_r = ((float)rand() / (RAND_MAX)) + 1;
			rand_color_g = ((float)rand() / (RAND_MAX)) + 1;
			rand_color_b = ((float)rand() / (RAND_MAX)) + 1;
			// cubes[i * CUBE_ROW + j]->SetColor(glm::vec4(rand_color_r-1.0f, rand_color_g-1.0f, rand_color_b-1.0f, 1.0f));
			cubes[i * CUBE_ROW + j]->SetPosition(square_pos + glm::vec3(-10.0f * i, 0.5f, -10.0f*j));
		}
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glEnable (GL_BLEND);
	glEnable(GL_CULL_FACE);
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	/* timing stuff */
	double angle, elapsed_time, speed;
	angle=elapsed_time=speed=0;
	double start_time = glfwGetTime();

	while (!window->isClosed()) {
		window->Clear();
		debug::calcFPS(window->GetGLFWwindow(), 1.0, "Neon Engine - Current FPS: ");

		/*******************************************
		* TIME BASED MOVEMENT - THIS ISN'T WORKING *
		*******************************************/
		elapsed_time = glfwGetTime() - start_time;
		speed = 10.0f * (std::max(elapsed_time, 0.03) * (1/30.0f));
		angle = angle + speed;
		if (angle > 360.0) {
			angle = 0;
		}
		
		//
		// Draw the plane
		//
		glm::mat4 plane_model_matrix = model * glm::translate(glm::vec3(0, -2.5f, 0)) * glm::scale(glm::vec3(100.0f, 0, 100.0f));
		plane.SetModelMatrix(plane_model_matrix);
		plane.Draw();

		//
		// Draw the cubes
		//
		for(int i=0; i < cubes.size(); ++i) {
			cubes[i]->SetRotation((float)angle, glm::vec3(0, 1, 0));
			cubes[i]->Draw();
		}

		window->Update();

		start_time = glfwGetTime();
	}

	for(int i=0; i < cubes.size(); ++i) {
		delete cubes[i];
	}

	return EXIT_SUCCESS;
}