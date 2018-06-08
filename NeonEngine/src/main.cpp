#include "./app/window.h"
#include "./app/scene.h"
#include "./app/input/eventManager.h"
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

const int WIDTH = 1024,
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
	float g_FAR = 500.0f;

	Camera camera(glm::vec3(0, 5.0f, -10.0f), FOV, ASPECT_RATIO, g_NEAR, g_FAR);
	float camera_rotate_speed = (M_PI/180) * 0.8;

	glm::mat4 view_projection = camera.GetViewProjection();
	glm::mat4 model = glm::mat4(1.0f);

	/* GLFW is initialized within the window */
	Window *window = new Window(WIDTH, HEIGHT, false, "Neon Engine");
	Input *inputManager = window->GetInput();
	window->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	Scene myScene;
	myScene.LoadSettings("./NeonEngine/src/res/settings/testSceneSettings.init");

	/***********************
		  Light Stuff
	***********************/
	glm::vec3 lightAmbient(0.2f),
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

	instancedProgram->SetUniform3f("viewPos", camera.GetPosition());
	instancedProgram->SetUniform1f("material.shininess", 32.0f);
	instancedProgram->Unbind();

	// Set up normal program
	program->Bind();
	program->SetUniformMat4("view_projection", view_projection);
	program->SetUniform3f("light.position", lightPos);
	program->SetUniform3f("light.ambient", lightAmbient);
	program->SetUniform3f("light.specular", lightSpecular);

	program->SetUniform3f("viewPos", camera.GetPosition());
	program->SetUniform1f("material.shininess", 32.0f);
	program->Unbind();

	// Set Up simple program
	simpleProgram->Bind();
	simpleProgram->SetUniformMat4("view_projection", view_projection);
	simpleProgram->Unbind();

	unsigned int instanced_light_pos_loc = instancedProgram->GetUniformLocation("light.position"),
				 program_light_pos_loc = program->GetUniformLocation("light.position");
	
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
			transforms[i * CUBE_ROW + j].SetScale(glm::vec3(0.2, 0.2, 0.2));
		}
	}
	instanced_cubes.SetTransforms(transforms);
	
	//
	// Timer variables
	//
	double angle, elapsed_time, speed;
	angle=elapsed_time=speed=0;
	double last_time = glfwGetTime(), current_time = 0;

	//
	// Camera Variables
	//
	float camera_speed = 0.0f;
	float camera_acceleration = 0.8f;
	float camera_speed_limit = 2.0f;


	//
	// Light movement variables
	//
	short direction = -1;
	float light_speed = 100.0;

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
	glfwSetInputMode(window->GetGLFWwindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Todo: Test a callback that passes a variable to manipulate a variable
	// inputManager->BindEvent("CameraMove", NEON_KEY_EVENT, Callback<>(MoveCameraFunc));
	inputManager->BindEvent("CameraMoveAround", NEON_CURSOR_EVENT, Callback<>(MoveCameraAroundFunc));

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

	/**************************
	** MAIN APPLICATION LOOP **
	***************************/
	while (!window->isClosed()) {
		window->Clear();
		debug::calcFPS(window->GetGLFWwindow(), 1.0, "Neon Engine - Current FPS: ");

		// Handle cube rotations
		current_time = glfwGetTime();
		elapsed_time = current_time - last_time;
		speed = 2.0f;

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

		MoveCameraFunc();
		camera.Update();
		view_projection = camera.GetViewProjection();

		//
		// Handle Camera Updates
		//
		instancedProgram->Bind();
		instancedProgram->SetUniform3f(instanced_light_pos_loc, lightPos);
		instancedProgram->SetUniformMat4("view_projection", view_projection);
		instancedProgram->SetUniform3f("viewPos", camera.GetPosition());
		program->Bind();
		program->SetUniform3f(program_light_pos_loc, lightPos);
		program->SetUniformMat4("view_projection", view_projection);
		program->SetUniform3f("viewPos", camera.GetPosition());
		simpleProgram->Bind();
		simpleProgram->SetUniformMat4("view_projection", view_projection);

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
		instanced_cubes.UpdateAllTransforms(transforms, new_transform);
		instanced_cubes.Draw();

		window->Update();

		last_time = current_time;
	}

	return EXIT_SUCCESS;
}