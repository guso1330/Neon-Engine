#include "./vertexArray.h"

namespace neon {
	VertexArray::VertexArray() {
		GL_Call(glGenVertexArrays(1, &m_vao));
		m_vbo = nullptr;
		m_ibo = nullptr;
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
