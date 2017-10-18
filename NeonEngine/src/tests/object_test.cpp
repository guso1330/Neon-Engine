#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../app/window.h"
#include "../shaders/shader.h"
#include "../graphics/buffers/vertexBuffer.h"
#include "../graphics/buffers/indexBuffer.h"
#include "../graphics/buffers/vertexArray.h"
#include "../graphics/cameras/camera.h"
#include "../graphics/entities/model.h"
#include "../utils/obj_loader/objloader.h"
#include "../utils/debugging/printing_functions.cpp"

using namespace neon;
using namespace glm;

const GLint WIDTH = 1024,
			HEIGHT = 768;

int run_object_test() {
	// Initialize the camera
	float ASPECT_RATIO = (float)WIDTH/(float)HEIGHT;
	float FOV = 70.0f;
	float NEAR = 0.1f;
	float FAR = 1000.0f;
	Camera camera(glm::vec3(0, 0, -3.5), FOV, ASPECT_RATIO, NEAR, FAR);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view_projection = camera.GetViewProjection();

	Window *window = new Window(WIDTH, HEIGHT, false, "Simple Rectangle Test");
	window->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Model obj1("./NeonEngine/src/res/models/suzanne.obj");

	/***********************************
		Need to create an application
		class that has the capability
		of attaching shaders to it
	***********************************/
	Shader *vShader = new Shader("./NeonEngine/src/res/shaders/basicVShader.glsl", GL_VERTEX_SHADER);
	Shader *fShader = new Shader("./NeonEngine/src/res/shaders/basicFShader.glsl", GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();
	glAttachShader(program, vShader->GetShaderID());
	glAttachShader(program, fShader->GetShaderID());
	glLinkProgram(program);
	
	GLint linkStatus;
	glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		GLint logLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		GLchar *linkerLog = new GLchar[logLength + 1];
		glGetProgramInfoLog(program, logLength + 1, NULL, linkerLog);

		std::cerr << "Program failed to link: " << linkerLog << std::endl;
		system("PAUSE");
		return EXIT_FAILURE;
	}
	glUseProgram(program);
	/**********************************/

	GLuint model_loc = glGetUniformLocation(program, "model");
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	GLuint view_projection_loc = glGetUniformLocation(program, "view_projection");
	glUniformMatrix4fv(view_projection_loc, 1, GL_FALSE, &view_projection[0][0]);

	// glEnable(GL_DEPTH_TEST);
	// glEnable (GL_BLEND);
	// glDepthFunc(GL_LEQUAL);
	// glClearDepth(1.0f);
	// glEnable(GL_CULL_FACE);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	while (!window->isClosed()) {
		window->Clear();

		obj1.Draw();

		window->Update();
	}

	glDeleteProgram(program);

	return EXIT_SUCCESS;
}