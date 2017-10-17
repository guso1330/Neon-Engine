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

void VertexArray::Bind() const {
	glBindVertexArray(m_vao);
}

void VertexArray::Unbind() const {
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(VertexBuffer *buffer, GLuint index) {
	// m_buffers.push(buffer);
	Bind();
	buffer->Bind();
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, (void*)0);
	buffer->Unbind();
	Unbind();
}