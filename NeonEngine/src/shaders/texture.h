#pragma once

#include "../core/platform/opengl/GL_Error.h"

#include <glad/glad.h>
#include <string>

using namespace std;

namespace neon {
	enum TextureType {
		Diffuse,
		Normal,
		Specular,
		Height,
		Occlusion
	};
	class Texture {

		public:
			Texture(const std::string& filename, TextureType type = Diffuse);
			~Texture();

			void Bind(unsigned int unit) const;
			void Unbind(unsigned int unit) const;

		public:
			// GETTERS	
			inline const GLuint& GetID() const { return m_texID; }
			inline const std::string GetFilename() const { return m_filename; }
			inline const int GetWidth() const { return m_width; }
			inline const int GetHeight() const { return m_height; }
			inline const TextureType GetType() const { return m_type; }

		private:

			GLuint m_texID;
			std::string m_filename;
			int m_width, m_height;
			TextureType m_type;
	};
}