#include "./indexBuffer.h"

namespace neon {
	IndexBuffer::IndexBuffer() {
		GL_Call(glGenBuffers(1, &m_ibo));
	}

	IndexBuffer::~IndexBuffer() {
		GL_Call(glDeleteBuffers(1, &m_ibo));
	}

	void IndexBuffer::Bind() const {
		GL_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	}

	void IndexBuffer::Unbind() const {
		GL_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void IndexBuffer::SetBufferData(const unsigned int* data, size_t count) {
		m_count = count;
		GL_Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
	}

	void IndexBuffer::SetBufferData(const std::vector<unsigned int> &data) {
		m_count = data.size();
		GL_Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &data.front(), GL_STATIC_DRAW));
	}
}
