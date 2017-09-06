#include "./vertexBuffer.h"

using namespace neon;

VertexBuffer::VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount)
	: m_componentCount(componentCount) {
	// Generate a new buffer
	glGenBuffers(1, &m_vbo);
	bind();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
	unbind();
}

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}