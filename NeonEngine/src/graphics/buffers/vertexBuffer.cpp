#include "./vertexBuffer.h"

using namespace neon;

VertexBuffer::VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount)
	: m_componentCount(componentCount) {
	// Generate a new buffer
	glGenBuffers(1, &m_vbo);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW);
	Unbind();
}

VertexBuffer::VertexBuffer(const std::vector<glm::vec3> &data)
	: m_componentCount(3) {
	// Generate a new buffer
	glGenBuffers(1, &m_vbo);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), &data[0][0], GL_STATIC_DRAW);
	Unbind();
}

void VertexBuffer::Bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void VertexBuffer::Unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}