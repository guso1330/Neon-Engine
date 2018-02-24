#pragma once

// #include "../../engine/GL_Error.h"
#include "./vertexBuffer.h"
#include "./vertexBufferLayout.h"

#include <glad/glad.h>
#include <vector>
#include <iostream>

namespace neon {
	class VertexArray {
		public:
			VertexArray();
			~VertexArray();

			// Getters
			const unsigned int &GetVao() const { return m_vao; }

			void Bind() const;
			void Unbind() const;
			void PushBuffer(const VertexBuffer *buffer, const VertexBufferLayout& layout, int start_index = 0);
			void UpdateVertexAttribs(const VertexBufferLayout& layout, int start_index = 0);
			void SetVertexAttribDivisor(unsigned int index, unsigned int divisor);
		private:
			unsigned int m_vao;
			std::vector<const VertexBuffer*> m_buffers;
	};
}