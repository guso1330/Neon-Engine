#pragma once

#include "../../engine/GL_Error.h"
#include "./vertexBuffer.h"
#include "./vertexBufferLayout.h"

#include <glad/glad.h>
#include <vector>

namespace neon {
	class VertexArray {
		public:
			VertexArray();
			~VertexArray();

			// Getters
			const unsigned int &GetVao() const { return m_vao; }

			void Bind() const;
			void Unbind() const;
			void AddBuffer(const VertexBuffer *buffer, const VertexBufferLayout& layout, const int i);
		private:
			unsigned int m_vao;
			std::vector<VertexBuffer*> m_buffers;
	};
}