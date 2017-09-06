#pragma once

#include <glad/glad.h>

namespace neon {
	class VertexBuffer {
		private:
			GLuint m_componentCount;
			GLuint m_vbo;
		public:
			VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount);
			~VertexBuffer() {}
			void bind() const;
			void unbind() const;
			inline GLuint getComponentCount() { return m_componentCount; }
	};
}