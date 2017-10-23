#include "texture.h"
#include <cassert>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION // needed to use the stb_image library
#include <stb_image.h>

Texture::Texture(const std::string& filename) {
	/* LOAD THE IMAGE DATA */
	m_filename = filename;

	int numComponents; // Image properties
	unsigned char* image_data = stbi_load(filename.c_str(), &m_width, &m_height, &numComponents, 4); // Load the image

	if(image_data == NULL) { // error checking
		std::cerr << "Texture loading failed for texture: " << filename << std::endl;
	} else {
		glGenTextures(1, &m_texID); // Generate space for the texture
		glBindTexture(GL_TEXTURE_2D, m_texID);
		
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
		
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}


	stbi_image_free(image_data);
}

Texture::~Texture() {
	glDeleteTextures(1, &m_texID); // delete the texture
}

void Texture::Bind(unsigned int unit) {
	assert(unit >= 0 && unit <= 31);
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texID);	
}