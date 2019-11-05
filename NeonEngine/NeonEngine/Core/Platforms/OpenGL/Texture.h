#pragma once

#include "Graphics/Renderers/ITexture.h"
#include "Core/Platforms/OpenGL/GL_Error.h"

#include <glad/glad.h>
#include <string>

using namespace std;

namespace Neon { namespace OpenGL {
	class Texture : public ITexture {

		public:
			Texture(const std::string& filename, TextureType type = TextureType::DIFFUSE);
			~Texture();

			virtual void Bind(unsigned int unit = 0) const override;
			virtual void Unbind(unsigned int unit = 0) const override;

		public:
			// GETTERS	
			inline const unsigned int& GetId() const { return m_texId; }
			inline const std::string GetFilename() const { return m_filename; }
			inline virtual const unsigned int GetWidth() const override { return m_width; }
			inline virtual const unsigned int GetHeight() const override { return m_height; }
			inline const TextureType GetType() const { return m_type; }

		private:

			unsigned int m_texId;
			std::string m_filename;
			unsigned int m_width, m_height;
			TextureType m_type;
	};
}}
