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

void VertexArray::AddBuffer(const VertexBuffer *buffer, const VertexBufferLayout& layout, int i = 0) {
	Bind(); // bind vao
	buffer->Bind(); // bind vbo

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for(; i < elements.size(); ++i) {
		const auto& element = elements[i];
		GL_Call(glEnableVertexAttribArray(i));
		GL_Call(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (void*)offset));
		offset += i * VertexBufferElement::GetSizeOfType(element.type);
	}
}