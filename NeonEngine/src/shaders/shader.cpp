#include "shader.h"

namespace neon {
	Shader::Shader(const char* shaderFile, GLenum shaderType) :
		m_filename(shaderFile),
		m_type(shaderType)
	{
		initShader();
	}

	Shader::~Shader() { glDeleteShader(m_shaderID); }

	GLuint Shader::initShader() {
		m_source = readShaderSource(m_filename);
		if (m_source == NULL) {
			std::cerr << "Failed to read " << m_filename << std::endl;
			exit(EXIT_FAILURE);
		}

		GLuint program = glCreateProgram();
		m_shaderID = glCreateShader(m_type);
		glShaderSource(m_shaderID, 1, (const GLchar**)&m_source, NULL);
		glCompileShader(m_shaderID);

		GLint compiled;
		glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &compiled);
		// Get compile errors and log them
		if (!compiled) {
			std::cerr << m_filename << " failed to compile: " << std::endl;
			GLint logSize;
			glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetShaderInfoLog(m_shaderID, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;

			exit(EXIT_FAILURE);
		}

		delete[] m_source;
		glAttachShader(program, m_shaderID);

		// Link and error check
		glLinkProgram(program);

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
			std::cerr << "Shader program gailed to link" << std::endl;
			GLint logSize;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetProgramInfoLog(program, logSize, NULL, logMsg);
			std::cerr << logMsg << std::endl;
			delete[] logMsg;

			exit(EXIT_FAILURE);
		}

		glUseProgram(program);
		return program;
	}

	char* Shader::readShaderSource(const char* shaderFile) {
		FILE* fp = fopen(shaderFile, "r");

		if (fp == NULL) {
		return NULL;
		}

		fseek(fp, 0L, SEEK_END);
		long size = ftell(fp);

		fseek(fp, 0L, SEEK_SET);
		char* buf = new char[size + 1];
		fread(buf, 1, size, fp);

		buf[size] = '\0';
		fclose(fp);

		return buf;
	}
}