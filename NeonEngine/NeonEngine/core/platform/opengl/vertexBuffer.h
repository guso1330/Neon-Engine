#pragma once

#include "./GL_Error.h"
#include "./bufferLayout.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Neon {

	class VertexBuffer {
		public:
			// Constructors
			VertexBuffer();
			VertexBuffer(unsigned int usage);

			// Destructor
			~VertexBuffer();

			inline const unsigned int GetId() { return m_vbo; }

			void Bind() const;
			void Unbind() const;
			void Resize(size_t size);

			void SetLayout(BufferLayout bufferLayout);
			void SetBufferData(const void* data, size_t size) const;

		private:
			BufferLayout m_layout;
			unsigned int m_usage;
			size_t m_size;
			unsigned int m_vbo;
	};
}