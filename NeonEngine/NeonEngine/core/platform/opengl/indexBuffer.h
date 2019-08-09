#pragma once

#include "./GL_Error.h"

#include <glad/glad.h>
#include <iostream>
#include <vector>

namespace neon {
	class IndexBuffer {
		public:
			IndexBuffer();
			~IndexBuffer();

			// Getters
			inline const unsigned int GetId() { return m_ibo; }
			inline unsigned int GetCount() { return m_count; }

			void Bind() const;
			void Unbind() const;

			void SetBufferData(const unsigned int* data, size_t count);
			void SetBufferData(const std::vector<unsigned int> &data);

		private:
			unsigned int m_count;
			unsigned int m_ibo;
	};
}