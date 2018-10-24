#pragma once

#include "../../../app/window.h"
#include "./GL_Error.h"
#include "./vertexArray.h"
#include "./shader.h"
#include "./program.h"
#include "./texture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

namespace neon {
	typedef std::unordered_map<unsigned int, VertexArray*> VertexArrayMap;
	typedef std::unordered_map<unsigned int, Shader*> ShaderMap;
	typedef std::unordered_map<unsigned int, Program*> ProgramMap;
	typedef std::unordered_map<unsigned int, Texture*> TextureMap;

	class OpenGLContext {
		public:
			// Constructor
			OpenGLContext();

			//
			// Public Functional Methods
			//
			void Clear() const;
			void Draw(unsigned int vao_id, unsigned int num_elements, unsigned int draw_mode);

			//
			// Create methods
			//
			unsigned int CreateVao(const void* data, size_t data_size, const unsigned int* indices, unsigned int indices_count, BufferLayout layout, VertexBuffer::BufferUsage usage);
			unsigned int CreateShader(const std::string& filename, unsigned int shader_type);
			unsigned int CreateProgram(const unsigned int shader_ids[], unsigned int size);
			unsigned int CreateTexture(const std::string& filename, TextureType type, unsigned int unit);

			//
			// Get Program
			//
			inline Program* GetProgram(unsigned int program_id) { return m_programMap[program_id]; }

			//
			// Set Methods
			//
			void SetClearColor(float r, float g, float b, float a);

			//
			// Binding Methods
			//
			void BindTexture(unsigned int tex_id, unsigned int unit);
			void BindVao(unsigned int vao_id);
			void BindProgram(unsigned int program_id);


		//
		// Private Methods
		//
		private:
			bool Init();

		//
		// Private Variables
		//
		private:
			glm::vec4 m_clearColor;
			unsigned int m_currentVao;
			unsigned int m_currentProgram;

		// Private Structures/Containers
		private:
			VertexArrayMap m_vaoMap;
			ShaderMap m_shaderMap;
			ProgramMap m_programMap;
			TextureMap m_textureMap;
	};
}
