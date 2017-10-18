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
		glUseProgram(m_programID);
	}
}