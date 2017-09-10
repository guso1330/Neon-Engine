#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <vector>

namespace neon {
	class VertexBuffer {
		private:
			GLuint m_componentCount;
			GLuint m_vbo;
		public:
			// Constructors
			VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount);
			VertexBuffer(std::vector<glm::vec3> &data);
			// Destructor
			~VertexBuffer() {}
			void bind() const;
			void unbind() const;
			inline GLuint getComponentCount() { return m_componentCount; }
	};
}