#pragma once

#include "./GL_Error.h"

#include <glad/glad.h>
#include <iostream>
#include <vector>

namespace neon {

	class UniformBuffer {
		public:
			UniformBuffer();
			~UniformBuffer();

			// Getters
			inline const unsigned int &GetUbo() { return m_ubo; }

			void Bind() const;
			void Unbind() const;

			void SetBufferData(const unsigned int* data, size_t size, unsigned int usage);

		private:
			unsigned int m_ubo;
	};
}