#include "./app/window.h"
#include "./shaders/shader.h"
#include "./shaders/program.h"
#include "./graphics/buffers/vertexBuffer.h"
#include "./graphics/buffers/indexBuffer.h"
#include "./graphics/buffers/vertexArray.h"
#include "./graphics/cameras/camera.h"
#include "./graphics/entities/model.h"
#include "./graphics/entities/gameobject.h"
#include "./graphics/entities/renderableCollection.h"
#include "./graphics/entities/transform.h"
#include "./utils/obj_loader/objloader.h"
#include "./utils/debugging/debug.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <time.h>

#include <glm/glm.hpp>

using namespace neon;
using namespace glm;

const GLint WIDTH = 768,
			HEIGHT = 540;

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

	Camera camera(glm::vec3(0, 15.0f, -50.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	camera.SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 view_projection = camera.GetViewProjection();
	glm::mat4 model = glm::mat4(1.0f);

	/* GLFW is initialized within the window */
	Window *window = new Window(WIDTH, HEIGHT, false, "Neon Engine");
	window->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/***********************
		  Light Stuff
	***********************/
	glm::vec3 lightAmbient(0.3f),
			  lightDiffuse(0.9f),
			  lightSpecular(0.5f),
			  lightPos(0.0, 25.0, 0.0);

	/************************************
		Setting up Shaders and Program
		------------------------------
		Need to create an application
		class that has the capability
		of attaching shaders to it
	*************************************/
	Shader *simpleVShader = new Shader("./NeonEngine/src/res/shaders/basicVShader.glsl", GL_VERTEX_SHADER);
	Shader *simpleFShader = new Shader("./NeonEngine/src/res/shaders/basicFShader.glsl", GL_FRAGMENT_SHADER);
	Shader *vShader = new Shader("./NeonEngine/src/res/shaders/textureVShader.glsl", GL_VERTEX_SHADER);
	Shader *instancedVShader = new Shader("./NeonEngine/src/res/shaders/instancedVShader.glsl", GL_VERTEX_SHADER);
	Shader *lightingFShader = new Shader("./NeonEngine/src/res/shaders/lightingFShader.glsl", GL_FRAGMENT_SHADER);

	std::vector<Shader*> shaders, instancedShaders, simpleShaders;
	shaders.push_back(vShader);
	shaders.push_back(lightingFShader);
	instancedShaders.push_back(instancedVShader);
	instancedShaders.push_back(lightingFShader);
	simpleShaders.push_back(simpleVShader);
	simpleShaders.push_back(simpleFShader);

	Program *instancedProgram = new Program(instancedShaders),
			*program = new Program(shaders),
			*simpleProgram = new Program(simpleShaders);

	// Set up the instanced program
	instancedProgram->Bind();
	instancedProgram->SetUniformMat4("view_projection", view_projection);
	instancedProgram->SetUniform3f("light.position", lightPos);
	instancedProgram->SetUniform3f("light.ambient", lightAmbient);
	instancedProgram->SetUniform3f("light.diffuse", lightDiffuse);
	instancedProgram->SetUniform3f("light.specular", lightSpecular);

	instancedProgram->SetUniform3f("viewPos", camera.GetPos());
	instancedProgram->SetUniform1f("material.shininess", 32.0f);
	instancedProgram->Unbind();

	// Set up normal program
	program->Bind();
	program->SetUniformMat4("view_projection", view_projection);
	program->SetUniform3f("light.position", lightPos);
	program->SetUniform3f("light.ambient", lightAmbient);
	program->SetUniform3f("light.specular", lightSpecular);

	program->SetUniform3f("viewPos", camera.GetPos());
	program->SetUniform1f("material.shininess", 32.0f);
	program->Unbind();

	// Set Up simple program
	simpleProgram->Bind();
	simpleProgram->SetUniformMat4("view_projection", view_projection);
	simpleProgram->Unbind();
	
	/***************************
		Setting up The Models
	****************************/
	Model plane("./NeonEngine/src/res/models/plane_5unit.obj", program);
	Model cube_model("./NeonEngine/src/res/models/plasmacannon/plasma cannon.x", instancedProgram);
	Model sphere_model("./NeonEngine/src/res/models/sphere.obj", simpleProgram);
	/**********************************/
	
	/***************************
		Setting up The Textures
	****************************/
	Texture cube_tex("./NeonEngine/src/res/models/plasmacannon/plasmacannon_weapon_diffuse.bmp", Diffuse),
			cube_spec_tex("./NeonEngine/src/res/models/plasmacannon/plasmacannon_weapon_specular.jpg", Specular),
			plane_tex("./NeonEngine/src/res/textures/cartoon_floor_texture.jpg", Diffuse);
	/**********************************/
	plane.SetTexture(&plane_tex, Diffuse);
	glm::mat4 plane_model_matrix = model * glm::translate(glm::vec3(0, -2.5f, 0)) * glm::scale(glm::vec3(100.0f, 0, 100.0f));
	program->Bind();
	plane.GetTransform().SetModelMatrix(plane_model_matrix);
	program->Unbind();

	cube_model.SetTexture(&cube_tex, Diffuse);
	cube_model.SetTexture(&cube_spec_tex, Specular);
	// rand_color_r = ((float)rand() / (RAND_MAX)) + 1;
	// rand_color_g = ((float)rand() / (RAND_MAX)) + 1;
	// rand_color_b = ((float)rand() / (RAND_MAX)) + 1;
	// cube_model.SetColor(glm::vec4(rand_color_r, rand_color_g, rand_color_b, 1.0f));

	RenderableCollection instanced_cubes(&cube_model, instancedProgram);

	sphere_model.SetColor(glm::vec4(1.0f));
	GameObject sphere(&sphere_model);
	sphere.SetPosition(lightPos);


	// Set transform rotation and position
	std::vector<Transform> transforms(CUBE_COL * CUBE_ROW);
	glm::vec3 square_pos = glm::vec3(245.0f, 0.5f, 245.0f);
	for(int i=0; i<CUBE_COL; ++i) {
		for(int j=0; j < CUBE_COL; ++j) {
			transforms[i * CUBE_ROW + j].SetPosition(square_pos + glm::vec3(-10.0f * i, 0.5f, -10.0f*j));
			transforms[i * CUBE_ROW + j].SetScale(glm::vec3(0.5, 0.5, 0.5));
		}
	}
	// instanced_cubes.UpdateAllTransforms(transforms, scale);

	//
	// OpenGL Setting
	//
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glEnable (GL_BLEND);
	glEnable(GL_CULL_FACE);
	glClearDepth(1.0f);
	glEnable(GL_MULTISAMPLE); // 4x MSAA is used in window.h
	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	//
	// Timer variables
	//
	double angle, elapsed_time, speed;
	angle=elapsed_time=speed=0;
	double last_time = glfwGetTime(), current_time = 0;

	//
	// Light movement variables
	//
	short direction = -1;
	float light_speed = 100.0;
	while (!window->isClosed()) {

		window->Clear();
		debug::calcFPS(window->GetGLFWwindow(), 1.0, "Neon Engine - Current FPS: ");

		/**********************
		* TIME BASED MOVEMENT *
		**********************/
		// Handle cube rotations
		current_time = glfwGetTime();
		elapsed_time = current_time - last_time;
		speed = 2.0f;

		// float rand_deviation = ((float)rand() / (2)) + -2;
		angle += (elapsed_time * speed);
		if (angle > 360.0) {
			angle = 0;
		}

		//
		// Handle light movement
		//
		lightPos.z += elapsed_time * (light_speed * direction);
		if(lightPos.z <= -200.0f) { direction *= -1; }
		else if(lightPos.z >= 200.0f) { direction *= -1; }		
		instancedProgram->Bind();
		instancedProgram->SetUniform3f("light.position", lightPos);
		instancedProgram->Unbind();
		program->Bind();
		program->SetUniform3f("light.position", lightPos);
		program->Unbind();

		//
		// Draw sphere (lamp)
		//
		sphere.SetPosition(lightPos);
		sphere.Draw();
		
		//
		// Draw the plane
		//
		plane.Draw();

		//
		// Draw the cubes
		//
		Transform new_transform;
		new_transform.SetRotation((float)angle, glm::vec3(0, 1, 0));
		new_transform.SetScale(glm::vec3(0.3));
		instanced_cubes.UpdateAllTransforms(transforms, new_transform);
		instanced_cubes.Draw();

		window->Update();

		last_time = current_time;
	}

	return EXIT_SUCCESS;
}