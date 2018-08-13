#pragma once

#include "./GL_Error.h"

#include <glad/glad.h>
#include <iostream>
#include <vector>

namespace neon {
	class IndexBuffer {
		public:
			IndexBuffer();
			IndexBuffer(unsigned int* data, GLsizei count);
			IndexBuffer(const std::vector<unsigned int> &data);
			~IndexBuffer();

			// Getters
			inline const unsigned int &GetIbo() { return m_ibo; }

			void Bind() const;
			void Unbind() const;
			inline unsigned int GetCount() { return m_count; }
		private:
			unsigned int m_count;
			unsigned int m_ibo;
	};
}