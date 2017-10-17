#pragma once

#include <glad/glad.h>
#include <iostream>

#include "../utils/file_utils/fileUtils.h"

namespace neon {

	class Shader {
		public:
			Shader(const char* shaderFile, GLenum shaderType);
			~Shader();
		private:
			void InitShader();
		public:
			inline GLuint GetShaderID() { return m_shaderID; }
		private:
			const char *m_filename;
			GLenum m_type;
			const GLchar *m_source;
			GLuint m_shaderID;
	};
}
