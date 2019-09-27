#include "./vertexArray.h"

namespace Neon {
	VertexArray::VertexArray() {
		GL_Call(glGenVertexArrays(1, &m_vao));
	}

	VertexArray::~VertexArray() {
		GL_Call(glDeleteVertexArrays(1, &m_vao));
	}

	void VertexArray::Bind() const {
		GL_Call(glBindVertexArray(m_vao));
	}

	void VertexArray::Unbind() const {
		GL_Call(glBindVertexArray(0));
	}
}
