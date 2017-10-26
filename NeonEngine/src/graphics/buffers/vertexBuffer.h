#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
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
			VertexBuffer(const std::vector<glm::vec2> &data);
			// Destructor
			~VertexBuffer() { glDeleteBuffers(1, &m_vbo); }
			void Bind() const;
			void Unbind() const;
			inline GLuint GetComponentCount() { return m_componentCount; }
	};
}