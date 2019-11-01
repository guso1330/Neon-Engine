#include "texture.h"
#include <cassert>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION // needed to use the stb_image library
#include <stb_image.h>

namespace Neon { namespace OpenGL {
	Texture::Texture(const std::string& filename, TextureType type) :
		m_type(type)
	{

		/* LOAD THE IMAGE DATA */
		m_filename = filename;

		int numComponents; // Image properties
		stbi_set_flip_vertically_on_load(1);
		unsigned char* image_data = stbi_load(filename.c_str(), &m_width, &m_height, &numComponents, 4); // Load the image

		if(image_data == NULL) { // error checking
			std::cerr << "Texture loading failed for texture: " << filename << std::endl;
			return;
		}
		
		GL_Call(glGenTextures(1, &m_texId)); // Generate space for the texture
		GL_Call(glBindTexture(GL_TEXTURE_2D, m_texId));

		GL_Call(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data));
		
		// Set Texture Parameters
		GL_Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GL_Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		GL_Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR));
		GL_Call(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GL_Call(glGenerateMipmap(GL_TEXTURE_2D));
			
		stbi_image_free(image_data);
	}

	Texture::~Texture() {
		GL_Call(glDeleteTextures(1, &m_texId)); // delete the texture
	}

	void Texture::Bind(unsigned int unit) const {
		assert(unit >= 0 && unit <= 31);
		GL_Call(glActiveTexture(GL_TEXTURE0 + unit));
		GL_Call(glBindTexture(GL_TEXTURE_2D, m_texId));
	}

	void Texture::Unbind(unsigned int unit) const {
		GL_Call(glActiveTexture(GL_TEXTURE0 + unit));
		GL_Call(glBindTexture(GL_TEXTURE_2D, 0));
	}
}}