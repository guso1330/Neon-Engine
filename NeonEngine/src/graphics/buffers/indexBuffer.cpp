#include "./indexBuffer.h"

using namespace neon;

IndexBuffer::IndexBuffer(unsigned int* data, GLsizei count)
	: m_count(count) {
	// Generate a new buffer
	glGenBuffers(1, &m_ibo);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
	Unbind();
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int> &data) {
	// Generate a new buffer
	m_count = data.size();
	glGenBuffers(1, &m_ibo);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), &data.front(), GL_STATIC_DRAW);
	Unbind();
}

IndexBuffer::~IndexBuffer() { glDeleteBuffers(1, &m_ibo); }

void IndexBuffer::Bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
}

void IndexBuffer::Unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}