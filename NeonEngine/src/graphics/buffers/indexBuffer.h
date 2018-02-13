#pragma once

#include "../../engine/GL_Error.h"

#include <glad/glad.h>
#include <iostream>
#include <vector>

namespace neon {
	class IndexBuffer {
		private:
			unsigned int m_count;
			unsigned int m_ibo;
		public:
			IndexBuffer(unsigned int* data, GLsizei count);
			IndexBuffer(const std::vector<unsigned int> &data);
			~IndexBuffer();
			void Bind() const;
			void Unbind() const;
			inline unsigned int GetCount() { return m_count; }
	};
}