#include "./VertexBuffer.h"

#include "Core/Core.h"

namespace Neon { namespace OpenGL {
	VertexBuffer::VertexBuffer(BufferUsage usage)
		: m_usage(usage)
	{
		// Generate a new buffer
		GL_Call(glGenBuffers(1, &m_vbo));
	}

	VertexBuffer::VertexBuffer(void* data, size_t size, const BufferLayout& bufferLayout)
		: m_usage(BufferUsage::STATIC)
	{
		GL_Call(glGenBuffers(1, &m_vbo));
		SetLayout(bufferLayout);
		SetBufferData(data, size);
	}

	VertexBuffer::~VertexBuffer() {
		Unbind();
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
		GL_Call(glBufferData(
			GL_ARRAY_BUFFER,
			size,
			NULL,
			ConvertBufferUsageToOpenGLUsage(m_usage)
		));
	}

	void VertexBuffer::SetBufferData(const void* data, size_t size) {
		m_size = size;
		Bind();
		GL_Call(glBufferData(
			GL_ARRAY_BUFFER,
			size,
			data,
			ConvertBufferUsageToOpenGLUsage(m_usage)
		));
	}
}}
