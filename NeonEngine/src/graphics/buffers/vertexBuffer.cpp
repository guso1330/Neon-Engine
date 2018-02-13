#include "./vertexBuffer.h"

using namespace neon;

VertexBuffer::VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount)
	: m_componentCount(componentCount) {
	// Generate a new buffer
	GL_Call(glGenBuffers(1, &m_vbo));
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW));
	Unbind();
}

VertexBuffer::VertexBuffer(const std::vector<glm::vec3> &data)
	: m_componentCount(3) {
	// Generate a new buffer
	GL_Call(glGenBuffers(1, &m_vbo));
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), &data[0][0], GL_STATIC_DRAW));
	Unbind();
}

VertexBuffer::VertexBuffer(const std::vector<glm::vec2> &data)
	: m_componentCount(2) {
	// Generate a new buffer
	GL_Call(glGenBuffers(1, &m_vbo));
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), &data[0][0], GL_STATIC_DRAW));
	Unbind();
}

// VertexBuffer(const std::vector<Transform> &data) {}

void VertexBuffer::Bind() const {
	GL_Call(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
}

void VertexBuffer::Unbind() const {
	GL_Call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}