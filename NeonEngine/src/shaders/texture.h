#pragma once

#include <glad/glad.h>
#include <string>

using namespace std;

class Texture {

	public:
		Texture(const std::string& filename);
		~Texture();

		void Bind(unsigned int unit);
	public:
		// GETTERS	
		inline const GLuint& GetID() const { return m_texID; }
		inline const std::string GetFilename() const { return m_filename; }
		inline const int GetWidth() const { return m_width; }
		inline const int GetHeight() const { return m_height; }

	private:
		Texture(const Texture& other) {} // copy constructor
		void operator=(const Texture& other) {}

		GLuint m_texID;
		std::string m_filename;
		int m_width, m_height;
};