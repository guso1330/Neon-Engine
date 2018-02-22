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

void VertexArray::PushBuffer(const VertexBuffer *buffer, const VertexBufferLayout& layout, int start_index) {
	Bind(); // bind vao
	buffer->Bind(); // bind vbo

	const auto& elements = layout.GetElements();
	for(int i = start_index; i < (elements.size() + start_index); ++i) {
		const auto& element = elements[i - start_index];
		GL_Call(glEnableVertexAttribArray(i));
		GL_Call(glVertexAttribPointer(i, element.count, element.type, element.normalized, element.size, (const void*)(element.offset)));
	}
}

void VertexArray::SetVertexAttribDivisor(unsigned int index, unsigned int divisor) {
	GL_Call(glVertexAttribDivisor(index, divisor));
}