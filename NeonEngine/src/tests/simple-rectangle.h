#include "../app/window.h"
#include "../shaders/shader.h"
#include "../graphics/buffers/vertexBuffer.h"
#include "../graphics/buffers/indexBuffer.h"
#include "../graphics/buffers/vertexArray.h"

using namespace neon;

const GLint WIDTH = 800,
			HEIGHT = 400;

int run_simple_rectangle() {
	Window *window = new Window(WIDTH, HEIGHT, false, "Simple Rectangle Test");
	window->setClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f, // top right
		 0.5f, -0.5f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f  // top left
	};
	GLushort indices[] = {  // note that we start from 0!
		0, 1, 3, // first Triangle
		1, 2, 3  // second Triangle
	};

	VertexArray VAO;
	VertexBuffer *VBO = new VertexBuffer(vertices, 4*3, 3);
	IndexBuffer EBO(indices, 6);
	
	VAO.addBuffer(VBO, 0);

	// unsigned int VBO, VAO, EBO;
	
	// // VAO
	// glGenVertexArrays(1, &VAO);
	// glBindVertexArray(VAO);

	// // VBO
	// glGenBuffers(1, &VBO);
	// glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// // EBO
	// glGenBuffers(1, &EBO);
	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
	// glEnableVertexAttribArray(0);
	// // GLuint loc = glGetAttribLocation(program, "vPosition");
	// // glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	// // glEnableVertexAttribArray(loc);

	while (!window->closed()) {
		window->clear();
		VAO.bind();
		EBO.bind();
		glDrawElements(GL_TRIANGLES, EBO.getCount(), GL_UNSIGNED_SHORT, 0);
		EBO.unbind();
		VAO.unbind();
		window->update();
	}
	// glDeleteVertexArrays(1, &VAO);
	// glDeleteBuffers(1, &VBO);
	// glDeleteBuffers(1, &EBO);
	glDeleteProgram(program);

	return EXIT_SUCCESS;
}