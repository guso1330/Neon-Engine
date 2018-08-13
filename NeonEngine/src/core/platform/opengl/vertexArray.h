#pragma once

#include "./GL_Error.h"
#include "./IBuffer.h"
#include "./bufferLayout.h"

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

			void PushBuffer(const IBuffer *buffer);


		private:
			unsigned int m_vao;
			std::vector<const IBuffer*> m_buffers;
	};
}