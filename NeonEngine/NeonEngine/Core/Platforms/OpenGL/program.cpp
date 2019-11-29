#include "nepch.h"

#include "Core/Platforms/OpenGL/Program.h"

namespace Neon { namespace OpenGL {
	Program::Program(const std::string& name, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath)
		: m_name(name)
	{
		std::shared_ptr<Shader> vertexShader = std::make_shared<Shader>(vertexShaderFilePath, ShaderType::VERTEX_SHADER);
		std::shared_ptr<Shader> fragmentShader = std::make_shared<Shader>(fragmentShaderFilePath, ShaderType::FRAGMENT_SHADER);

		m_Shaders.push_back(vertexShader);
		m_Shaders.push_back(fragmentShader);

		Init();
	}

	Program::Program(const std::string& name, std::shared_ptr<Shader>& vertexShader, std::shared_ptr<Shader> fragmentShader)
		: m_name(name)
	{
		m_Shaders.push_back(vertexShader);
		m_Shaders.push_back(fragmentShader);

		Init();
	}

	Program::~Program() { 
		Unbind();
		GL_Call(glDeleteProgram(m_programID));
	}

	void Program::Bind() {
		GL_Call(glUseProgram(m_programID));
	}

	void Program::Unbind() {
		GL_Call(glUseProgram(0));
	}

	void Program::Init() {
		m_programID = glCreateProgram();
		for(int i=0; i<m_Shaders.size(); ++i) {
			GL_Call(glAttachShader(m_programID, m_Shaders[i]->GetId()));
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
			NE_CORE_INFO("Program {} was created", this->GetId());
		}
	}

	int Program::GetUniformLocation(const std::string& name) {
		if(m_uniformLocationCache.find(name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[name];

		int loc = glGetUniformLocation(m_programID, name.c_str());
		if (loc == -1) {
			NE_CORE_WARN("Program {} glGetUniformLocation Error: could no locate the uniform {}", this->GetId(), name);
		}

		m_uniformLocationCache[name] = loc;
		return loc;
	}

	int Program::GetAttributeLocation(const std::string& name) {
		if(m_attributeLocationCache.find(name) != m_attributeLocationCache.end())
			return m_attributeLocationCache[name];

		int loc = glGetAttribLocation(m_programID, name.c_str());
		if (loc == -1) {
			NE_CORE_WARN("glGetAttribLocation Error: Could not locate the attribute {}", name);
		}

		m_attributeLocationCache[name] = loc;
		return loc;
	}

	/* Setters */
	// Matrix
	void Program::SetMat4(const std::string& name, const glm::mat4& matrix) {
		GL_Call(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
	}

	// Vec3
	void Program::SetFloat3(const std::string& name, const glm::vec3& v3) {
		GL_Call(glUniform3f(GetUniformLocation(name), v3.x, v3.y, v3.z));
	}

	// Vec4
	void Program::SetFloat4(const std::string& name, const glm::vec4& v4) {
		GL_Call(glUniform4f(GetUniformLocation(name), v4.x, v4.y, v4.z, v4.w));
	}

	// Int
	void Program::SetInt(const std::string& name, int v0) {
		GL_Call(glUniform1i(GetUniformLocation(name), v0));
	}
}}