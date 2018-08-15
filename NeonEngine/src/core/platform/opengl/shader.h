#pragma once

#include "./GL_Error.h"

#include <glad/glad.h>
#include <iostream>

#include "../../../utils/file_utils/fileUtils.h"

namespace neon {

	class Shader {
		public:
			Shader(const char* shaderFile, unsigned int shaderType);
			~Shader();

		private:
			void InitShader();

		public:
			inline unsigned int GetShaderId() { return m_shaderID; }
			inline unsigned int GetShaderType() { return m_type; }
			
		private:
			const char* m_filename;
			unsigned int m_type;
			const char* m_source;
			unsigned int m_shaderID;
	};
}
