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
			VertexBuffer(const std::vector<glm::vec3> &data);
			// Destructor
			~VertexBuffer() {}
			void Bind() const;
			void Unbind() const;
			inline GLuint GetComponentCount() { return m_componentCount; }
	};
}