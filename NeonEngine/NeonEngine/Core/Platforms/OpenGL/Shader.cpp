#include "Core/Core.h"
#include "Core/Platforms/OpenGL/Shader.h"

#include "Core/Platforms/OpenGL/GLHelpers.h"
#include "Utils/FileUtils/FileUtils.h"

namespace Neon { namespace OpenGL {	
	static const unsigned int GetGLShaderType(const ShaderType type) {
		switch(type) {
			case ShaderType::VERTEX_SHADER:
				return GL_VERTEX_SHADER;
			case ShaderType::FRAGMENT_SHADER:
				return GL_FRAGMENT_SHADER;
			case ShaderType::GEOMETRY_SHADER:
				return GL_GEOMETRY_SHADER;
			case ShaderType::COMPUTE_SHADER: break;
			default: break;
		}
		NE_CORE_ASSERT(false, "OpenGL Shader: That type of shader does not exist");
		return 0;
	}

	Shader::Shader(const std::string& filepath, const ShaderType type) :
		m_filename(filepath),
		m_type(type)
	{
		Init();
	}

	Shader::~Shader() { GL_Call(glDeleteShader(m_shaderID)); }

	void Shader::Init() {
		std::string str_source = read_file(m_filename);
		m_source = str_source.c_str();
		if (m_source == NULL) {
			std::string message = std::string("OpenGL Shader: Failed to read ") + m_filename;
			NE_CORE_ASSERT(false, message);
			return;
		}

		m_shaderID = glCreateShader(
			GetGLShaderType(m_type)
		);

		// Compile Shader Source
		GL_Call(glShaderSource(m_shaderID, 1, &m_source, NULL));
		GL_Call(glCompileShader(m_shaderID));

		int compiled;
		GL_Call(glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &compiled));

		// Get compile errors and log them
		if (!compiled) {
			int logSize;
			
			NE_CORE_ERROR("{} failed to compile: ", m_filename);

			GL_Call(glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &logSize));
			char* logMsg = (char*)alloca(logSize * sizeof(char));
			GL_Call(glGetShaderInfoLog(m_shaderID, logSize, &logSize, logMsg));
			std::cerr << logMsg << std::endl;
			
			GL_Call(glDeleteShader(m_shaderID));
			system("PAUSE");
			exit(EXIT_FAILURE);
		}
	}

	const unsigned int Shader::GetGLType() const {
		return GetGLShaderType(m_type);
	}
}}