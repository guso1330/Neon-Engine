#include "./indexBuffer.h"

using namespace neon;

IndexBuffer::IndexBuffer(GLuint* data, GLsizei count)
	: m_count(count) {
	// Generate a new buffer
	glGenBuffers(1, &m_ibo);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint), data, GL_STATIC_DRAW);
	unbind();
}

IndexBuffer::IndexBuffer(std::vector<GLuint> &data) {
	// Generate a new buffer
	m_count = data.size();
	glGenBuffers(1, &m_ibo);
	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(GLuint), &data.front(), GL_STATIC_DRAW);
	unbind();
}

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}