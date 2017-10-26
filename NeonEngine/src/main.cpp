#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include <glm/glm.hpp>

#include "./app/window.h"
#include "./shaders/shader.h"
#include "./shaders/program.h"
#include "./graphics/buffers/vertexBuffer.h"
#include "./graphics/buffers/indexBuffer.h"
#include "./graphics/buffers/vertexArray.h"
#include "./graphics/cameras/camera.h"
#include "./graphics/entities/model.h"
#include "./utils/obj_loader/objloader.h"
#include "./utils/debugging/printing_functions.cpp"

using namespace neon;
using namespace glm;

const GLint WIDTH = 1024,
			HEIGHT = 768;

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
	// Camera camera(glm::vec3(0, 300.0f, -300.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	Camera camera(glm::vec3(0, 75.0f, -75.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	// Camera camera(glm::vec3(0, 2.0f, -3.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	camera.SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 view_projection = camera.GetViewProjection();
	glm::mat4 rotation = glm::mat4(1.0f), model = glm::mat4(1.0f);

	/* GLFW is initialized within the window */
	Window *window = new Window(WIDTH, HEIGHT, false, "Simple Rectangle Test");
	window->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/************************************
		Setting up Shaders and Program
		------------------------------
		Need to create an application
		class that has the capability
		of attaching shaders to it
	*************************************/
#if _WIN32
	Shader *vShader = new Shader("../NeonEngine/src/res/shaders/basicVShader.glsl", GL_VERTEX_SHADER);
	Shader *fShader = new Shader("../NeonEngine/src/res/shaders/basicFShader.glsl", GL_FRAGMENT_SHADER);
#elif __APPLE__
	Shader *vShader = new Shader("./NeonEngine/src/res/shaders/textureVShader.glsl", GL_VERTEX_SHADER);
	Shader *fShader = new Shader("./NeonEngine/src/res/shaders/textureFShader.glsl", GL_FRAGMENT_SHADER);
#endif

	std::vector<Shader*> shaders;
	shaders.push_back(vShader);
	shaders.push_back(fShader);
	std::vector<Model*> models;
	Program *program = new Program(shaders);

	/***************************
		Setting up The Models
	****************************/
#if _WIN32
	Model obj1("../NeonEngine/src/res/models/only_quad_sphere.obj", program);
#elif __APPLE__

	// *WARNING: SEG FAULT WHEN USING THE PLASMACANNON
	// Model obj1("./NeonEngine/src/res/models/Plasmacannon/plasma_cannon.obj", program);
	// obj1.SetTexture("./NeonEngine/src/res/models/Plasmacannon/plasmacannon_weapon_diffuse.bmp");
	// Model obj1("./NeonEngine/src/res/models/cube_5unit_allfaceuvs.obj", program);
	// obj1.SetTexture("./NeonEngine/src/res/textures/checker.png");
	Model obj1("./NeonEngine/src/res/models/pepsi/Pepsi_Can.obj", program);
	obj1.SetTexture("./NeonEngine/src/res/models/pepsi/pepsi_simple.jpg");
	// for(int i=0; i < 10; ++i) {
	// 	models.push_back(new Model("./NeonEngine/src/res/models/cube.obj", program));
	// 	rand_color_r = ((float)rand() / (RAND_MAX)) + 1;
	// 	rand_color_g = ((float)rand() / (RAND_MAX)) + 1;
	// 	rand_color_b = ((float)rand() / (RAND_MAX)) + 1;
	// 	models[i]->SetColor(glm::vec4(rand_color_r-1.0f, rand_color_g-1.0f, rand_color_b-1.0f, 1.0f));
	// 	models[i]->SetTexture("./NeonEngine/src/res/textures/checkered_colored.jpg");
	// }
	Model plane("./NeonEngine/src/res/models/plane_5unit.obj", program);
	plane.SetTexture("./NeonEngine/src/res/textures/checkered_colored.jpg");
#endif

	// DEBUG
	// cout << "CUBE & PLANE UV's" << std::endl;
	// debug::print_vector_vec2(plane.GetMesh()->GetUVs());
	// debug::print_vector_uint(plane.GetMesh()->GetIndices());
	// debug::print_vector_vec2(models[0]->GetMesh()->GetUVs());
	// debug::print_vector_vec3(obj1.GetMesh()->GetVertices());
	// debug::print_vector_vec3(obj1.GetMesh()->GetNormals());
	// debug::print_vector_uint(obj1.GetMesh()->GetIndices());
	// debug::print_vector_vec2(obj1.GetMesh()->GetUVs());
	
	/**********************************/
	program->SetUniformMat4("view_projection", view_projection);

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
		debug::calcFPS(window->GetGLFWwindow(), 1.0, "Current FPS: ");

		/*******************************************
		* TIME BASED MOVEMENT - THIS ISN'T WORKING *
		*******************************************/
		elapsed_time = glfwGetTime() - start_time;
		speed = 10.0f * (std::max(elapsed_time, 0.03) * (1/30.0f));
		angle = angle + speed;
		if (angle >= 360.0) {
			angle = 0;
		}

		rotation = model * glm::rotate((float)angle, glm::vec3(0, 1, 0));
		obj1.SetModelMatrix(rotation);
		obj1.Draw();

		//
		// Draw the plane
		//
		glm::mat4 plane_model_matrix = model * glm::translate(glm::vec3(0, -0.5f, 0)) * glm::rotate(0.0f, glm::vec3(0, 0, 1)) * glm::scale(glm::vec3(10.0f, 0, 10.0f));
		plane.SetModelMatrix(plane_model_matrix);
		plane.Draw();

		//
		// Draw the cubes
		//
		// models[0]->SetModelMatrix(rotation);
		// models[0]->Draw();
		// for(int i=1; i<models.size()-1; ++i) {
		// 	rotation = model * glm::translate(glm::vec3(0, 0.5f, 3.0*i)) * glm::rotate((float)angle, glm::vec3(0, 1, 0));
		// 	models[i]->SetModelMatrix(rotation);
		// 	models[i]->Draw();
		// }

		window->Update();

		start_time = glfwGetTime();
	}

	for(int i=0; i<models.size(); ++i) {
		delete models[i];
	}
	return EXIT_SUCCESS;
}