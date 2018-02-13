#include "shader.h"

namespace neon {
	Shader::Shader(const char* shaderFile, GLenum shaderType) :
		m_filename(shaderFile),
		m_type(shaderType)
	{
		InitShader();
	}

	Shader::~Shader() { GL_Call(glDeleteShader(m_shaderID)); }

	void Shader::InitShader() {
		std::string str_source = read_file(m_filename);
		m_source = str_source.c_str();
		if (m_source == NULL) {
			std::cerr << "Failed to read " << m_filename << std::endl;
			system("PAUSE");
			exit(EXIT_FAILURE);
		}

		m_shaderID = glCreateShader(m_type);

		// Compile Shader Source
		GL_Call(glShaderSource(m_shaderID, 1, &m_source, NULL));
		GL_Call(glCompileShader(m_shaderID));

		GLint compiled;
		GL_Call(glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &compiled));
		// Get compile errors and log them
		if (!compiled) {
			std::cerr << "\n" << m_filename << " failed to compile: " << std::endl;
			
			GLint logSize;

			GL_Call(glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &logSize));
			char* logMsg = (char*)alloca(logSize * sizeof(char));
			GL_Call(glGetShaderInfoLog(m_shaderID, logSize, &logSize, logMsg));
			std::cerr << logMsg << std::endl;
			
			GL_Call(glDeleteShader(m_shaderID));
			system("PAUSE");
			exit(EXIT_FAILURE);
		}
	}
}