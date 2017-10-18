#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "./app/window.h"
#include "./shaders/shader.h"
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
	// Initialize the camera
	float ASPECT_RATIO = (float)WIDTH / (float)HEIGHT;
	float FOV = 70.0f;
	float g_NEAR = 0.1f;
	float g_FAR = 1000.0f;
	Camera camera(glm::vec3(0, 0, -3.5), FOV, ASPECT_RATIO, g_NEAR, g_FAR);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view_projection = camera.GetViewProjection();


	/* GLFW is initialized within the window */
	Window *window = new Window(WIDTH, HEIGHT, false, "Simple Rectangle Test");
	window->SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);

#if _WIN32
	Model obj1("../NeonEngine/src/res/models/suzanne.obj");
#elif __APPLE__
	Model obj1("./NeonEngine/src/res/models/only_quad_sphere.obj");
#endif

	/***********************************
	Need to create an application
	class that has the capability
	of attaching shaders to it
	***********************************/
#if _WIN32
	Shader *vShader = new Shader("../NeonEngine/src/res/shaders/basicVShader.glsl", GL_VERTEX_SHADER);
	Shader *fShader = new Shader("../NeonEngine/src/res/shaders/basicFShader.glsl", GL_FRAGMENT_SHADER);
#elif __APPLE__
	Shader *vShader = new Shader("./NeonEngine/src/res/shaders/basicVShader.glsl", GL_VERTEX_SHADER);
	Shader *fShader = new Shader("./NeonEngine/src/res/shaders/basicFShader.glsl", GL_FRAGMENT_SHADER);
#endif

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
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	double start_time = glfwGetTime();
	double angle = 0;

	while (!window->isClosed()) {
		double elapsed_time = glfwGetTime() - start_time;
		double speed = 60.0 * (elapsed_time / (1.0/60.0));
		angle = angle + speed;
		if (angle >= 360.0) {
			angle = 0;
		}
		//cout << "angle: " << angle << " elapsed_time: " << elapsed_time << " speed: " << speed << std::endl;
		window->Clear();

		glm::mat4 rotation = model * glm::rotate((float)angle, glm::vec3(0, 1, 0));

		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &rotation[0][0]);
		obj1.Draw();

		window->Update();
		start_time = glfwGetTime();
	}

	glDeleteProgram(program);

	return EXIT_SUCCESS;
}