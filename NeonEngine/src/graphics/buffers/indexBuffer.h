#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>

namespace neon {
	class IndexBuffer {
		private:
			GLuint m_count;
			GLuint m_ibo;
		public:
			IndexBuffer(GLuint* data, GLsizei count);
			IndexBuffer(const std::vector<GLuint> &data);
			~IndexBuffer() {}
			void Bind() const;
			void Unbind() const;
			inline GLuint GetCount() { return m_count; }
	};
}