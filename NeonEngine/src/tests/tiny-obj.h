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
	Camera camera(glm::vec3(0, 0, -5.0), FOV, ASPECT_RATIO, NEAR, FAR);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view_projection = camera.GetViewProjection();

	Window *window = new Window(WIDTH, HEIGHT, false, "Simple Rectangle Test");
	window->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// std::vector<vec3> VERTICES;
	// std::vector<GLuint> INDICES;
	// std::vector<vec2> UVS;
	// std::vector<vec3> NORMALS;

	// tiny_obj_loader_load_obj("./NeonEngine/src/res/models/sphere.obj", VERTICES, INDICES, UVS, NORMALS);

	Mesh obj("./NeonEngine/src/res/models/suzanne.obj");
	
	// std::cout << "VERTICES - size: " << VERTICES.size() << std::endl;
	// printVectorVec3(VERTICES);
	// std::cout << std::endl << std::endl;

	// std::cout << "INDICES - size: " << INDICES.size() << std::endl;
	// printVectorUnint(INDICES);
	// std::cout << std::endl << std::endl;

	Shader *vShader = new Shader("./NeonEngine/src/res/shaders/basicVShader.glsl", GL_VERTEX_SHADER);
	Shader *fShader = new Shader("./NeonEngine/src/res/shaders/basicFShader.glsl", GL_FRAGMENT_SHADER);

	GLuint program = glCreateProgram();
	glAttachShader(program, vShader->getShaderID());
	glAttachShader(program, fShader->getShaderID());
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

	VertexArray VAO;
	VertexBuffer *VBO = new VertexBuffer(obj.GetVertices());
	IndexBuffer EBO(obj.GetIndices());
	VAO.addBuffer(VBO, 0);

	GLuint model_loc = glGetUniformLocation(program, "model");
	GLuint view_projection_loc = glGetUniformLocation(program, "view_projection");
	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(view_projection_loc, 1, GL_FALSE, &view_projection[0][0]);


	glEnable(GL_DEPTH_TEST);
	glEnable (GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);
	glEnable(GL_CULL_FACE);
	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );


	while (!window->closed()) {
		window->clear();
		
		VAO.bind();
		EBO.bind();
		glDrawElements(GL_TRIANGLES, EBO.getCount(), GL_UNSIGNED_INT, 0);
		EBO.unbind();
		VAO.unbind();

		window->update();
	}
	glDeleteProgram(program);

	return EXIT_SUCCESS;
}