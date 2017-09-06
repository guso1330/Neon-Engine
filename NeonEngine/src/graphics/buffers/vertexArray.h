#pragma once

#include <glad/glad.h>
#include "./vertexBuffer.h"
#include <vector>

namespace neon {
	class VertexArray {
		private:
			GLuint m_vao;
			std::vector<VertexBuffer*> m_buffers;
		public:
			VertexArray();
			~VertexArray();
			void bind() const;
			void unbind() const;
			void addBuffer(VertexBuffer *buffer, GLuint index);
	};
}