#include <iostream>
#include <vector>
#include <string>
#include <time.h>

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

#include <glm/glm.hpp>

using namespace neon;

const GLint WIDTH = 1024,
			HEIGHT = 768;

short int CUBE_COL = 50, CUBE_ROW = 50;

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
	// Camera camera(glm::vec3(0, 50.0f, -40.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	Camera camera(glm::vec3(0, 250.0f, -400.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	// Camera camera(glm::vec3(0, 400.0f, -400.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	// Camera camera(glm::vec3(0, 750.0f, -750.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
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

	/***************************
		Setting up The Models
	****************************/
#if _WIN32
	//Model obj1("../NeonEngine/src/res/models/only_quad_sphere.obj", program);
	
	/*Model cube("../NeonEngine/src/res/models/cube_5unit_allfaceuvs.obj", program);
	cube.SetTexture("../NeonEngine/src/res/textures/checker.png");

	Model plane("../NeonEngine/src/res/models/plane_5unit.obj", program);
	plane.SetTexture("../NeonEngine/src/res/textures/cartoon_floor_texture.jpg");*/

	Model bench("../NeonEngine/src/res/models/bench/bench.obj", program);
	bench.SetTexture("../NeonEngine/src/res/models/bench/animal-texture_082.jpg");
#elif __APPLE__

	// Model obj1("./NeonEngine/src/res/models/Plasmacannon/plasma_cannon.obj", program);
	// obj1.SetTexture("./NeonEngine/src/res/models/Plasmacannon/plasmacannon_weapon_diffuse.bmp");

	// Model obj1("./NeonEngine/src/res/models/cube_5unit_allfaceuvs.obj", program);
	// obj1.SetTexture("./NeonEngine/src/res/textures/cartoon_wall_texture.jpg");

	// Model obj1("./NeonEngine/src/res/models/cube_no_normals.obj", program);
	// obj1.SetTexture("./NeonEngine/src/res/textures/cartoon_wall_texture.jpg");

	// Model obj1("./NeonEngine/src/res/models/only_quad_sphere.obj", program);
	// obj1.SetColor(glm::vec4(1.0f, 0, 0, 1.0f));
	// Model obj1("./NeonEngine/src/res/models/pepsi/Pepsi_Can.obj", program);
	// obj1.SetTexture("./NeonEngine/src/res/models/pepsi/pepsi_simple.jpg");
	// Model obj1("./NeonEngine/src/res/models/pokeball.obj", program);
	// obj1.SetTexture("./NeonEngine/src/res/textures/checkered_colored.jpg");


	// for(int i=0; i < CUBE_COUNT; ++i) {
	// 	models.push_back(new Model("./NeonEngine/src/res/models/cube_5unit_allfaceuvs.obj", program));
	// 	rand_color_r = ((float)rand() / (RAND_MAX)) + 1;
	// 	rand_color_g = ((float)rand() / (RAND_MAX)) + 1;
	// 	rand_color_b = ((float)rand() / (RAND_MAX)) + 1;
	// 	models[i]->SetColor(glm::vec4(rand_color_r-1.0f, rand_color_g-1.0f, rand_color_b-1.0f, 1.0f));
	// 	models[i]->SetTexture("./NeonEngine/src/res/textures/checker.png");
	// }

	Model cube("./NeonEngine/src/res/models/cube_5unit_allfaceuvs.obj", program);
	cube.SetTexture("./NeonEngine/src/res/textures/checker.png");

	Model plane("./NeonEngine/src/res/models/plane_5unit.obj", program);
	plane.SetTexture("./NeonEngine/src/res/textures/cartoon_floor_texture.jpg");
	
	// Model bench("./NeonEngine/src/res/models/bench/bench.obj", program);
	// bench.SetTexture("./NeonEngine/src/res/models/bench/animal-texture_082.jpg");

	// Model ah_25b("./NeonEngine/src/res/models/ah-24b/AN-24PB.obj", program);
	// ah_25b.SetTexture("./NeonEngine/src/res/models/ah-24b/body.jpg");

	// Model AKM("./NeonEngine/src/res/models/AKM/AKM.obj", program);
	// AKM.SetTexture("./NeonEngine/src/res/models/AKM/AKMS_Diff.tga");
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
		speed = 10.0f * (max(elapsed_time, 0.03) * (1/30.0f));
		angle = angle + speed;
		if (angle >= 360.0) {
			angle = 0;
		}

		// rotation = model * glm::rotate((float)angle, glm::vec3(0, 1, 0));
		// obj1.SetModelMatrix(rotation);
		// obj1.Draw();

		//
		// Draw the plane
		//
		/*glm::mat4 plane_model_matrix = model * glm::translate(glm::vec3(0, -2.5f, 0)) * glm::scale(glm::vec3(100.0f, 0, 100.0f));
		plane.SetModelMatrix(plane_model_matrix);
		plane.Draw();*/

		//
		// Draw the bench
		//
		rotation = model * glm::rotate((float)angle, glm::vec3(0, 1, 0));
		glm::mat4 bench_model_matrix = model * rotation * glm::scale(glm::vec3(0.01f, 0.01f, 0.01f));
		bench.SetModelMatrix(bench_model_matrix);
		bench.Draw();

		//
		// Draw the r8_ah_25b
		//
		// rotation = model * glm::rotate((float)angle, glm::vec3(0, 1, 0));
		// glm::mat4 ah_25b_model_matrix = model * rotation * glm::scale(glm::vec3(1.5f, 1.51f, 1.51f));
		// ah_25b.SetModelMatrix(ah_25b_model_matrix);
		// ah_25b.Draw();

		// Draw the AKM
		// rotation = model * glm::rotate((-1)*(float)angle, glm::vec3(0, 1, 0));
		// glm::mat4 akm_model_matrix = model * rotation * glm::scale(glm::vec3(0.2f, 0.2f, 0.2f));
		// AKM.SetModelMatrix(akm_model_matrix);
		// AKM.Draw();

		//
		// Draw the cubes
		//
		//glm::vec3 square_pos = glm::vec3(245.0f, 0.5f, 245.0f);
		//rotation = model * glm::translate(square_pos) * glm::rotate((float)angle, glm::vec3(0, 1, 0));
		
		//cube.SetModelMatrix(rotation);
		// rand_color_r = ((float)rand() / (RAND_MAX)) + 1;
		// rand_color_g = ((float)rand() / (RAND_MAX)) + 1;
		// rand_color_b = ((float)rand() / (RAND_MAX)) + 1;
		// cube.SetColor(glm::vec4(rand_color_r-1.0f, rand_color_g-1.0f, rand_color_b-1.0f, 1.0f));
		//cube.Draw();
		/*for(int i=1; i<CUBE_COL-1; ++i) {
			for(int j=0; j < CUBE_COL; ++j) {
				rand_color_r = ((float)rand() / (RAND_MAX)) + 1;
				rand_color_g = ((float)rand() / (RAND_MAX)) + 1;
				rand_color_b = ((float)rand() / (RAND_MAX)) + 1;
				cube.SetColor(glm::vec4(rand_color_r-1.0f, rand_color_g-1.0f, rand_color_b-1.0f, 1.0f));
				rotation = model * glm::translate(square_pos + glm::vec3(-10.0f * i, 0.5f, -10.0f*j)) * glm::rotate((float)angle, glm::vec3(0, 1, 0));
				cube.SetModelMatrix(rotation);
				cube.Draw();
			}
		}*/

		window->Update();

		start_time = glfwGetTime();
	}

	for(int i=0; i<models.size(); ++i) {
		delete models[i];
	}
	return EXIT_SUCCESS;
}