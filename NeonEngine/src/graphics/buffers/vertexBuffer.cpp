#include "./vertexBuffer.h"

using namespace neon;

VertexBuffer::VertexBuffer(GLfloat* data, GLsizei count, GLuint componentCount)
	: m_componentCount(componentCount) {
	// Generate a new buffer
	GL_Call(glGenBuffers(1, &m_vbo));
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const std::vector<glm::vec3> &data)
	: m_componentCount(3) {
	// Generate a new buffer
	GL_Call(glGenBuffers(1, &m_vbo));
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), &data[0][0], GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const std::vector<glm::vec2> &data)
	: m_componentCount(2) {
	// Generate a new buffer
	GL_Call(glGenBuffers(1, &m_vbo));
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec2), &data[0][0], GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const std::vector<glm::mat4> &data) {
	// Generate a new buffer
	GL_Call(glGenBuffers(1, &m_vbo));
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::mat4), &data.front(), GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const std::vector<Vertex> &data) {
	GL_Call(glGenBuffers(1, &m_vbo));
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(Vertex), &(*(data.begin())), GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(unsigned int size) {
	GL_Call(glGenBuffers(1, &m_vbo));
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STREAM_DRAW));
}

void VertexBuffer::BufferData(std::vector<glm::mat4> &data) const {
	Bind();
	GL_Call(glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::mat4), &data.front(), GL_STREAM_DRAW));
}

void VertexBuffer::Bind() const {
	GL_Call(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
}

void VertexBuffer::Unbind() const {
	GL_Call(glBindBuffer(GL_ARRAY_BUFFER, 0));
}