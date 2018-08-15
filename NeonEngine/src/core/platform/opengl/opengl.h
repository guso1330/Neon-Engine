#pragma once

#include "../../../app/window.h"
#include "./GL_Error.h"
#include "./vertexArray.h"
#include "./shader.h"
#include "./program.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <vector>
#include <iostream>

namespace neon {
	typedef std::map<unsigned int, VertexArray*> VertexMap;
	typedef std::map<unsigned int, Shader*> ShaderMap;
	typedef std::map<unsigned int, Program*> ProgramMap;

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
			unsigned int CreateShader(const char* filename, unsigned int shaderType);
			unsigned int CreateProgram(const unsigned int shader_ids[], unsigned int size);

			//
			// Get Program
			//
			inline Program* GetProgram(unsigned int program_id) { return m_programMap[program_id]; }

			//
			// Set Methods
			//
			void SetClearColor(float r, float g, float b, float a);

		//
		// Private Methods
		//
		private:
			bool Init();
			void SetProgram(unsigned int program_id);

		//
		// Private Variables
		//
		private:
			glm::vec4 m_clearColor;
			unsigned int m_currentProgram;

		// Private Structures/Containers
		private:
			VertexMap m_vaoMap;
			ShaderMap m_shaderMap;
			ProgramMap m_programMap;
	};
}
