#include "./vertexArray.h"

using namespace neon;

VertexArray::VertexArray() {
	glGenVertexArrays(1, &m_vao);
}

VertexArray::~VertexArray() {
	for(int i=0; i < m_buffers.size(); ++i) {
		delete m_buffers[i];
	}
}

void VertexArray::bind() const {
	glBindVertexArray(m_vao);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

void VertexArray::addBuffer(VertexBuffer *buffer, GLuint index) {
	// m_buffers.push(buffer);
	bind();
	buffer->bind();
	glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(index);
	buffer->unbind();
	unbind();
}