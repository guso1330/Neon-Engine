#include "./vertexArray.h"

namespace neon {
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

	void VertexArray::BindVbo(unsigned int index) const {
		m_vbos[index]->Bind();
	}

	void VertexArray::PushBuffer(const VertexBuffer* vbo) {
		m_vbos.push_back(vbo);
	}
}
