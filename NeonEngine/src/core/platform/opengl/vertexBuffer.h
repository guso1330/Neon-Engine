#pragma once

#include "./GL_Error.h"
#include "./bufferLayout.h"
#include "./IBuffer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace neon {
	enum class BufferUsage
	{
		STATIC, DYNAMIC
	};

	class VertexBuffer : public IBuffer {

		static unsigned int GLBufferUsage(BufferUsage usage) {
			switch(usage) {
				case BufferUsage::STATIC:
					return GL_STATIC_DRAW;
				case BufferUsage::DYNAMIC:
					return GL_DYNAMIC_DRAW;
				default: break;
			}
			return 0;
		}

		public:
			// Constructors
			VertexBuffer();
			VertexBuffer(BufferUsage usage);
			VertexBuffer(BufferUsage usage, BufferLayout layout, const void* data, size_t size);

			// Destructor
			~VertexBuffer() { glDeleteBuffers(1, &m_vbo); }

			void Bind() const;
			void Unbind() const;
			void Resize(size_t size);

			void SetLayout(BufferLayout bufferLayout);
			void SetBufferData(const void* data, size_t size) const;

		private:
			BufferLayout m_layout;
			BufferUsage m_usage;
			size_t m_size;
			unsigned int m_vbo;
	};
}