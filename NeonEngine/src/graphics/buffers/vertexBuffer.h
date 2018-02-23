#pragma once

#include "../entities/transform.h"
#include "../entities/vertex.h"
#include "../../engine/GL_Error.h"

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <vector>

namespace neon {
	class VertexBuffer {
		private:
			// TODO: Can you remove the component count? It's not necessary with
			//		 bufferLayout class
			GLuint m_componentCount;
			GLuint m_vbo;

		public:
			// Constructors
			VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount);
			VertexBuffer(const std::vector<glm::vec3> &data);
			VertexBuffer(const std::vector<glm::vec2> &data);
			VertexBuffer(const std::vector<glm::mat4> &data);
			VertexBuffer(const std::vector<Vertex> &data);
			VertexBuffer(unsigned int size); // GL_STREAM_DRAW buffer

			// Destructor
			~VertexBuffer() { glDeleteBuffers(1, &m_vbo); }
			void Bind() const;
			void Unbind() const;

			void BufferData(std::vector<glm::mat4> &data) const;

			inline GLuint GetComponentCount() { return m_componentCount; }
	};
}