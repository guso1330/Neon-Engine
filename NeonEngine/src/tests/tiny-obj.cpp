#include <iostream>
#include <vector>
#include <glm/glm.hpp>

#include "../app/window.h"
#include "../shaders/shader.h"
#include "../graphics/buffers/vertexBuffer.h"
#include "../graphics/buffers/indexBuffer.h"
#include "../graphics/buffers/vertexArray.h"
#include "../graphics/cameras/camera.h"
#include "../graphics/entities/mesh.h"
#include "../utils/obj_loader/objloader.h"

using namespace neon;
using namespace glm;

const GLint WIDTH = 1024,
			HEIGHT = 768;

void printVectorVec3(const std::vector<vec3> &v) {
	for(int i=0; i<v.size(); ++i) {
		std::cout << "Vertex " << i << ": " << v[i].x << ", " << v[i].y << ", " << v[i].z << std::endl;
	}
}

void printVectorUnint(const std::vector<GLuint> &v) {
	for(int i=0; i<v.size(); i += 3) {
		std::cout << "Index " << i << ": " << v[i] << ", " << v[i+1] << ", " << v[i+2] << std::endl;
	}
}

int run_tiny_obj() {
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

	Mesh *obj1 = new Mesh("./NeonEngine/src/res/models/only_quad_sphere.obj");
	Mesh *obj2 = new Mesh("./NeonEngine/src/res/models/cube.obj");

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

	VertexArray Sprite1, Sprite2;
	IndexBuffer EBO1(obj1->GetIndices());
	IndexBuffer EBO2(obj2->GetIndices());
	
	Sprite1.AddBuffer(new VertexBuffer(obj1->GetVertices()), 0);
	Sprite2.AddBuffer(new VertexBuffer(obj2->GetVertices()), 0);

	GLuint model_loc = glGetUniformLocation(program, "model");
	GLuint view_projection_loc = glGetUniformLocation(program, "view_projection");
	glUniformMatrix4fv(view_projection_loc, 1, GL_FALSE, &view_projection[0][0]);

	glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glEnable(GL_CULL_FACE);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	while (!window->isClosed()) {
		window->Clear();
		
		Sprite1.Bind();
		EBO1.Bind();
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
		glDrawElements(GL_TRIANGLES, EBO1.GetCount(), GL_UNSIGNED_INT, 0);
		EBO1.Unbind();
		Sprite1.Unbind();

		Sprite2.Bind();
		EBO2.Bind();
		mat4 model2 = glm::translate(model, glm::vec3(2.0f, 0, 0));
		glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model2[0][0]);
		glDrawElements(GL_TRIANGLES, EBO2.GetCount(), GL_UNSIGNED_INT, 0);
		EBO2.Unbind();
		Sprite2.Unbind();

		window->Update();
	}

	delete obj1;
	delete obj2;

	glDeleteProgram(program);

	return EXIT_SUCCESS;
}