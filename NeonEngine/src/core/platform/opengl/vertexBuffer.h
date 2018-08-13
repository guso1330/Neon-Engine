#pragma once

#include "./GL_Error.h"
#include "./bufferLayout.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace neon {
	class VertexBuffer : public IBuffer {

		enum class BufferUsage
		{
			STATIC, DYNAMIC
		};

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
			VertexBuffer(BufferUsage usage, BufferLayout layout, const void* data, unsigned int size);

			// Destructor
			~VertexBuffer() { glDeleteBuffers(1, &m_vbo); }

			void Bind() const;
			void Unbind() const;
			void Resize(unsigned int size);

			void SetLayout(BufferLayout bufferLayout);
			void SetBufferData(const void* data, unsigned int size) const;

		private:
			BufferLayout m_layout;
			BufferUsage m_usage;
			unsigned int m_size;
			unsigned int m_vbo;
	};
}