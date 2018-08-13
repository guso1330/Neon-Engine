#include "./vertexArray.h"

using namespace neon;

VertexArray::VertexArray() {
	GL_Call(glGenVertexArrays(1, &m_vao));
}

VertexArray::~VertexArray() {
	GL_Call(glDeleteVertexArrays(1, &m_vao));
}

void VertexArray::Bind() const {
	GL_Call(glBindVertexArray(m_vao));
}

void VertexArray::Unbind() const {
	GL_Call(glBindVertexArray(0));
}



void VertexArray::PushBuffer(const IBuffer *buffer) {
	m_buffers.push_back(buffer);
}