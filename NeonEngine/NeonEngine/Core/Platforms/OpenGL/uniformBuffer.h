#pragma once

#include <iostream>
#include <vector>

namespace Neon { namespace OpenGL {
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
}}
