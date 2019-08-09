#include "./uniformBuffer.h"

namespace neon {
	UniformBuffer::UniformBuffer() {
		GL_Call(glGenBuffers(1, &m_ubo));
	}

	UniformBuffer::~UniformBuffer() {
		GL_Call(glDeleteBuffers(1, &m_ubo));
	}

	void UniformBuffer::Bind() const {
		GL_Call(glBindBuffer(GL_UNIFORM_BUFFER, m_ubo));
	}

	void UniformBuffer::Unbind() const {
		GL_Call(glBindBuffer(GL_UNIFORM_BUFFER, 0));
	}

	void UniformBuffer::SetBufferData(const unsigned int* data, size_t size, unsigned int usage) {
		GL_Call(glBufferData(GL_UNIFORM_BUFFER, size, data, usage));
	}
}