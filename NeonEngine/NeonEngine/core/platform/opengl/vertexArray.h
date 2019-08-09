#pragma once

#include "./GL_Error.h"
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
			const unsigned int GetVao() const { return m_vao; }

			void Bind() const;
			void Unbind() const;

		private:
			unsigned int m_vao;
	};
}