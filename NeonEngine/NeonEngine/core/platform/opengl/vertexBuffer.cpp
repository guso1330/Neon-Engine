#include "./vertexBuffer.h"

namespace Neon {
	VertexBuffer::VertexBuffer() {}

	VertexBuffer::VertexBuffer(unsigned int usage)
		: m_usage(usage) {
		// Generate a new buffer
		GL_Call(glGenBuffers(1, &m_vbo));
	}

	VertexBuffer::~VertexBuffer() { 
		GL_Call(glDeleteBuffers(1, &m_vbo));
	}

	void VertexBuffer::Bind() const {
		GL_Call(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	}

	void VertexBuffer::Unbind() const {
		GL_Call(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::Resize(size_t size) {
		m_size = size;
		GL_Call(glBufferData(GL_ARRAY_BUFFER, size, NULL, m_usage));
	}

	void VertexBuffer::SetLayout(BufferLayout bufferLayout) {
		m_layout = bufferLayout;
		const auto& layout = m_layout.GetLayout();
		for(size_t i = 0; i < layout.size(); ++i) {
			const auto& element = layout[i];
			GL_Call(glEnableVertexAttribArray(i));
			GL_Call(glVertexAttribPointer(i, element.count, element.type, element.normalized, m_layout.GetStride(), (const void*)(element.offset)));
		}
	}

	void VertexBuffer::SetBufferData(const void* data, size_t size) const {
		GL_Call(glBufferData(GL_ARRAY_BUFFER, size, data, m_usage));
	}
}
