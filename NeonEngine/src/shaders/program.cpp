#include "./program.h"

namespace neon {
	Program::Program(std::vector<Shader*> shaders) :
		m_shaders(shaders)
	{
		Init();
	}

	Program::~Program() { 
		Unbind();
		GL_Call(glDeleteProgram(m_programID));
	}

	void Program::Init() {
		m_programID = glCreateProgram();
		for(int i=0; i<m_shaders.size(); ++i) {
			GL_Call(glAttachShader(m_programID, m_shaders[i]->GetShaderID()));
		}
		GL_Call(glLinkProgram(m_programID));

		GLint linkStatus;
		GL_Call(glGetProgramiv(m_programID, GL_LINK_STATUS, &linkStatus));
		if (linkStatus != GL_TRUE) {
			GLint logLength;
			GL_Call(glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength));

			GLchar *linkerLog = new GLchar[logLength + 1];
			GL_Call(glGetProgramInfoLog(m_programID, logLength + 1, NULL, linkerLog));

			std::cerr << "Program failed to link: " << linkerLog << std::endl;
			system("PAUSE");
		} else {
			std::cout << "Program " << this->GetProgramID() << " was created" << std::endl;
		}
	}

	int Program::GetUniformLocation(const char* name) {
		if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		GLint loc = glGetUniformLocation(m_programID, name);
		if (loc == -1) {
			std::cerr << "Program " << this->GetProgramID() << " glGetUniformLocation Error: Could not locate the the uniform " << name << std::endl;
		}

		m_uniformLocationCache[name] = loc;
		return loc;
	}

	int Program::GetAttributeLocation(const char* name) {
		if(m_attributeLocationCache.find(name) != m_attributeLocationCache.end())
			return m_attributeLocationCache[name];

		GLint loc = glGetAttribLocation(m_programID, name);
		if (loc == -1) {
			std::cerr << "glGetAttribLocation Error: Could not locate the the attribute " << name << std::endl;
		}

		m_attributeLocationCache[name] = loc;
		return loc;
	}

	// Matrix
	void Program::SetUniformMat4(const char* name, const glm::mat4& matrix) {
		GL_Call(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}

	void Program::SetUniformMat4(GLuint loc, const glm::mat4& matrix) {
		GL_Call(glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]));
	}

	void Program::SetUniformMat3(const char* name, const glm::mat3& matrix) {
		GL_Call(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}

	void Program::SetUniformMat3(GLuint loc, const glm::mat3& matrix) {
		GL_Call(glUniformMatrix3fv(loc, 1, GL_FALSE, &matrix[0][0]));
	}

	// Vec4
	void Program::SetUniform4f(GLuint loc, const glm::vec4& v4) {
		GL_Call(glUniform4f(loc, v4.x, v4.y, v4.z, v4.w));
	}

	void Program::SetUniform4f(const char* name, const glm::vec4& v4) {
		GL_Call(glUniform4f(GetUniformLocation(name), v4.x, v4.y, v4.z, v4.w));
	}

	// Vec3
	void Program::SetUniform3f(GLuint loc, const glm::vec3& v3) {
		GL_Call(glUniform3f(loc, v3.x, v3.y, v3.z));
	}

	void Program::SetUniform3f(const char* name, const glm::vec3& v3) {
		GL_Call(glUniform3f(GetUniformLocation(name), v3.x, v3.y, v3.z));
	}

	// Float
	void Program::SetUniform1f(const char* name, GLfloat v0) {
		GL_Call(glUniform1f(GetUniformLocation(name), v0));
	}

	void Program::SetUniform1i(const char* name, GLint v0) {
		GL_Call(glUniform1i(GetUniformLocation(name), v0));
	}

	void Program::Bind() {
		GL_Call(glUseProgram(m_programID));
	}

	void Program::Unbind() {
		GL_Call(glUseProgram(0));
	}
}