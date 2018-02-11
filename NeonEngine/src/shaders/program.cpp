#include "./program.h"

namespace neon {
	Program::Program(std::vector<Shader*> shaders) :
		m_shaders(shaders)
	{
		Init();
	}

	Program::~Program() { glDeleteProgram(m_programID); }

	void Program::Init() {
		m_programID = glCreateProgram();
		for(int i=0; i<m_shaders.size(); ++i) {
			glAttachShader(m_programID, m_shaders[i]->GetShaderID());
		}
		glLinkProgram(m_programID);

		GLint linkStatus;
		glGetProgramiv(m_programID, GL_LINK_STATUS, &linkStatus);
		if (linkStatus != GL_TRUE) {
			GLint logLength;
			glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength);

			GLchar *linkerLog = new GLchar[logLength + 1];
			glGetProgramInfoLog(m_programID, logLength + 1, NULL, linkerLog);

			std::cerr << "Program failed to link: " << linkerLog << std::endl;
			system("PAUSE");
		}
		Bind();
	}

	GLint Program::GetUniformLocation(const char* name) {
		GLint loc = glGetUniformLocation(m_programID, name);
		if (loc == -1) {
			std::cerr << "Could not locate the the uniform " << name << std::endl;
			system("PAUSE");
		}
		return loc;
	}

	void Program::SetUniformMat4(const char* name, const glm::mat4& matrix) {
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	void Program::SetUniformMat4(GLuint loc, const glm::mat4& matrix) {
		glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
	}

	void Program::SetUniform4f(GLuint loc, const glm::vec4& v4) {
		glUniform4f(loc, v4.x, v4.y, v4.z, v4.w);
	}

	void Program::SetUniform1i(const char* name, GLfloat v0) {
		glUniform1i(GetUniformLocation(name), v0);
	}

	void Program::Bind() {
		glUseProgram(m_programID);
	}

	void Program::Unbind() {
		glUseProgram(0);
	}
}