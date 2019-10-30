#include "nepch.h"

#include "./program.h"

namespace Neon { namespace OpenGL {
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
			GL_Call(glAttachShader(m_programID, m_shaders[i]->GetShaderId()));
		}
		GL_Call(glLinkProgram(m_programID));

		int linkStatus;
		GL_Call(glGetProgramiv(m_programID, GL_LINK_STATUS, &linkStatus));
		if (linkStatus != GL_TRUE) {
			int logLength;
			GL_Call(glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &logLength));

			char *linkerLog = new char[logLength + 1];
			GL_Call(glGetProgramInfoLog(m_programID, logLength + 1, NULL, linkerLog));

			NE_CORE_ERROR("Program failed to link: {}", linkerLog);
			system("PAUSE");
		} else {
			NE_CORE_INFO("Program {} was created", this->GetProgramId());
		}
	}

	int Program::GetUniformLocation(const char* name) {
		if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		int loc = glGetUniformLocation(m_programID, name);
		if (loc == -1) {
			NE_CORE_WARN("Program {} glGetUniformLocation Error: could no locate the uniform {}", this->GetProgramId(), name);
		}

		m_uniformLocationCache[name] = loc;
		return loc;
	}

	int Program::GetAttributeLocation(const char* name) {
		if(m_attributeLocationCache.find(name) != m_attributeLocationCache.end())
			return m_attributeLocationCache[name];

		int loc = glGetAttribLocation(m_programID, name);
		if (loc == -1) {
			NE_CORE_WARN("glGetAttribLocation Error: Could not locate the attribute {}", name);
		}

		m_attributeLocationCache[name] = loc;
		return loc;
	}

	// Matrix
	void Program::SetUniformMat4(const char* name, const glm::mat4& matrix) {
		GL_Call(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}

	void Program::SetUniformMat4(unsigned int loc, const glm::mat4& matrix) {
		GL_Call(glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]));
	}

	void Program::SetUniformMat3(const char* name, const glm::mat3& matrix) {
		GL_Call(glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}

	void Program::SetUniformMat3(unsigned int loc, const glm::mat3& matrix) {
		GL_Call(glUniformMatrix3fv(loc, 1, GL_FALSE, &matrix[0][0]));
	}

	// Vec4
	void Program::SetUniform4f(unsigned int loc, const glm::vec4& v4) {
		GL_Call(glUniform4f(loc, v4.x, v4.y, v4.z, v4.w));
	}

	void Program::SetUniform4f(const char* name, const glm::vec4& v4) {
		GL_Call(glUniform4f(GetUniformLocation(name), v4.x, v4.y, v4.z, v4.w));
	}

	// Vec3
	void Program::SetUniform3f(unsigned int loc, const glm::vec3& v3) {
		GL_Call(glUniform3f(loc, v3.x, v3.y, v3.z));
	}

	void Program::SetUniform3f(const char* name, const glm::vec3& v3) {
		GL_Call(glUniform3f(GetUniformLocation(name), v3.x, v3.y, v3.z));
	}

	// Float
	void Program::SetUniform1f(const char* name, float v0) {
		GL_Call(glUniform1f(GetUniformLocation(name), v0));
	}

	void Program::SetUniform1i(const char* name, int v0) {
		GL_Call(glUniform1i(GetUniformLocation(name), v0));
	}


	void Program::SaveUniform(unsigned int block, std::string uniformBlockName) {
		
	}

	void Program::Bind() {
		GL_Call(glUseProgram(m_programID));
	}

	void Program::Unbind() {
		GL_Call(glUseProgram(0));
	}

}}