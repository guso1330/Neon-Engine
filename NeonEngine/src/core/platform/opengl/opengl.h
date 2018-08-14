#pragma once

#include "../../../app/window.h"
#include "./GL_Error.h"
#include "./vertexArray.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <iostream>

namespace neon {
	typedef std::map<unsigned int, VertexArray*> VertexMap;

	class OpenGLContext {
		public:
			// Constructor
			OpenGLContext();

			// Public Methods
			bool Init();
			void Clear() const;

			unsigned int CreateVao(const void* data, size_t data_size, const unsigned int* indices, unsigned int indices_count, BufferLayout layout, VertexBuffer::BufferUsage usage);

			void Draw(unsigned int vao_id, unsigned int num_elements, unsigned int draw_mode);

			// Set Methods
			void SetClearColor(float r, float g, float b, float a);

		private:
			glm::vec4 m_clearColor;

			VertexMap m_vaoMap;
	};
}
