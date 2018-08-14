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

			void BindVbo(unsigned int index) const;

			void PushBuffer(const VertexBuffer *buffer);

		private:
			unsigned int m_vao;
			std::vector<const VertexBuffer*> m_vbos;
	};
}