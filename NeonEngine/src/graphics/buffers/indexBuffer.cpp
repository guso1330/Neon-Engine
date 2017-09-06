#include "./indexBuffer.h"

using namespace neon;

IndexBuffer::IndexBuffer(GLushort* data, GLsizei count)
	: m_count(count) {
	// Generate a new buffer
	glGenBuffers(1, &m_ibo);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), data, GL_STATIC_DRAW);
	unbind();
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}