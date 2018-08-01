#include "./indexBuffer.h"

using namespace neon;

IndexBuffer::IndexBuffer() {
	GL_Call(glGenBuffers(1, &m_ibo));
}

IndexBuffer::IndexBuffer(unsigned int* data, GLsizei count)
	: m_count(count) {
	// Generate a new buffer
	GL_Call(glGenBuffers(1, &m_ibo));
	Bind();
	GL_Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int> &data) {
	// Generate a new buffer
	m_count = data.size();
	GL_Call(glGenBuffers(1, &m_ibo));
	Bind();
	GL_Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &data.front(), GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer() { GL_Call(glDeleteBuffers(1, &m_ibo)); }

void IndexBuffer::Bind() const {
	GL_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
}

void IndexBuffer::Unbind() const {
	GL_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}