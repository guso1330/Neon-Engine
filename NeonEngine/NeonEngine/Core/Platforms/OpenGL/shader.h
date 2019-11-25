#pragma once

#include "Core/Platforms/OpenGL/GL_Error.h"
#include "Graphics/Shaders/IShader.h"

#include <glad/glad.h>
#include <iostream>

namespace Neon { namespace OpenGL {
	class Shader : public IShader {
		public:
			Shader(const std::string& filepath, const ShaderType type);
			virtual ~Shader();

			/* Getters */
			inline const unsigned int GetId() const { return m_shaderID; }
			inline virtual const ShaderType GetType() const override { return m_type; }
			const unsigned int GetGLType() const;

		private:
			void Init();

		private:
			std::string m_filename;
			ShaderType m_type;
			const char* m_source;
			unsigned int m_shaderID;
	};
}}
