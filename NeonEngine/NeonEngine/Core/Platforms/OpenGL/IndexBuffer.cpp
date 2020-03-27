#include "Core/Platforms/OpenGL/IndexBuffer.h"

#include "Core/Platforms/OpenGL/GLHelpers.h" // includes glad.h

namespace Neon { namespace OpenGL {
	IndexBuffer::IndexBuffer() {
		GL_Call(glGenBuffers(1, &m_ibo));
	}

	IndexBuffer::IndexBuffer(unsigned int* indices, size_t size) {
		GL_Call(glGenBuffers(1, &m_ibo));
		SetBufferData(indices, size);
	}

	IndexBuffer::~IndexBuffer() {
		Unbind();
		GL_Call(glDeleteBuffers(1, &m_ibo));
	}

	void IndexBuffer::Bind() const {
		GL_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo));
	}

	void IndexBuffer::Unbind() const {
		GL_Call(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}

	void IndexBuffer::SetBufferData(const unsigned int* indices, size_t count) {
		m_count = count;
		Bind();
		GL_Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW));
	}

	void IndexBuffer::SetBufferData(const std::vector<unsigned int> &indices) {
		m_count = indices.size();
		Bind();
		GL_Call(glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices.front(), GL_STATIC_DRAW));
	}
}}
