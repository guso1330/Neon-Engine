#pragma once

#include "./GL_Error.h"
#include "./bufferLayout.h"
#include "./vertexBuffer.h"
#include "./indexBuffer.h"

#include <glad/glad.h>
#include <vector>
#include <iostream>

namespace neon {
	class VertexArray {
		public:
			VertexArray();
			~VertexArray();

			// Getters
			const unsigned int GetVao() const { return m_vao; }

			void Bind() const;
			void Unbind() const;

			void BindVbo(VertexBuffer* buffer);
			void BindIbo(IndexBuffer* buffer);
			
			void BindAllBuffers();

		private:
			unsigned int m_vao;
			VertexBuffer* m_vbo;
			IndexBuffer* m_ibo;
	};
}