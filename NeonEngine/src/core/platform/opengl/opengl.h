#pragma once

#include "../../../app/window.h"
#include "./GL_Error.h"
#include "./vertexArray.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <iostream>

namespace neon {
	class OpenGLContext {
		public:
			// Constructor
			OpenGLContext();

			// Public Methods
			bool Init();
			void Clear() const;

			// Get Methods
			unsigned int CreateVao(const void* data, size_t data_size, const unsigned int* indices, unsigned int indices_count, BufferLayout layout, VertexBuffer::BufferUsage usage);

			// Set Methods
			void SetClearColor(float r, float g, float b, float a);

		private:
			glm::vec4 m_clearColor;

			std::map<unsigned int, VertexArray*> m_vaoMap;
	};
}
