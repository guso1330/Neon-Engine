#include "./vertexArray.h"

using namespace neon;

VertexArray::VertexArray() {
	GL_Call(glGenVertexArrays(1, &m_vao));
}

VertexArray::~VertexArray() {
	for(int i=0; i < m_buffers.size(); ++i) {
		delete m_buffers[i];
	}

	GL_Call(glDeleteVertexArrays(1, &m_vao));
}

void VertexArray::Bind() const {
	GL_Call(glBindVertexArray(m_vao));
}

void VertexArray::Unbind() const {
	GL_Call(glBindVertexArray(0));
}

void VertexArray::AddBuffer(VertexBuffer *buffer, GLuint index) {
	// m_buffers.push(buffer);
	Bind();
	buffer->Bind();
	GL_Call(glEnableVertexAttribArray(index));
	// TODO: this only works with one sprite, because of the stride and pointer
	GL_Call(glVertexAttribPointer(index, buffer->GetComponentCount(), GL_FLOAT, GL_FALSE, 0, (void*)0));
	buffer->Unbind();
	Unbind();
}