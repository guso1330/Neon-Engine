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
			IndexBuffer(std::vector<GLuint> &data);
			~IndexBuffer() {}
			void bind() const;
			void unbind() const;
			inline GLuint getCount() { return m_count; }
	};
}