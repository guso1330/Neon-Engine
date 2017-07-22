#pragma once

#include <glad\glad.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>

namespace neon {

	class Shader {
		public:
			Shader(const char* shaderFile, GLenum shaderType);
			~Shader();
		private:
			// Create a NULL-terminated string by reading the provided file
			static char* readShaderSource(const char* shaderFile);
			GLuint initShader();
		public:
			inline GLuint getShaderID() { return m_shaderID; }
		private:
			const char* m_filename;
			GLenum m_type;
			GLchar *m_source;
			GLuint m_shaderID;
	};
}