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

void VertexArray::PushBuffer(const VertexBuffer *buffer, const VertexBufferLayout& layout, int start_index) {
	Bind(); // bind vao
	buffer->Bind(); // bind vbo

	// NOTE: in renderableCollection::SetUpBufferData the buffer needs to be removed from m_buffers 
	UpdateVertexAttribs(layout, start_index);
}

void VertexArray::UpdateVertexAttribs(const VertexBufferLayout& layout, int start_index) {
	const auto& elements = layout.GetElements();
	for(int i = start_index; i < (elements.size() + start_index); ++i) {
		const auto& element = elements[i - start_index];
		GL_Call(glEnableVertexAttribArray(i));
		GL_Call(glVertexAttribPointer(i, element.count, element.type, element.normalized, element.size, (const void*)(element.offset)));
	}
}

void VertexArray::DisableVertexAttribs(unsigned int start_index, unsigned int end_index) {
	for(; start_index <= end_index; ++start_index)
		GL_Call(glDisableVertexAttribArray(start_index));
}

void VertexArray::SetVertexAttribDivisor(unsigned int index, unsigned int divisor) {
	GL_Call(glVertexAttribDivisor(index, divisor));
}

void VertexArray::SetVertexAttribDivisors(unsigned int i, unsigned int index_end, unsigned int divisor) {
	for(; i <= index_end; ++i) {
		GL_Call(glVertexAttribDivisor(i, divisor));
	}
}