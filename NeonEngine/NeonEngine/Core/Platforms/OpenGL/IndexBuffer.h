#pragma once

#include "Graphics/Renderers/IIndexBuffer.h"

#include <iostream>
#include <vector>

namespace Neon { namespace OpenGL {
	class IndexBuffer : public IIndexBuffer {
		public:
			IndexBuffer();
			IndexBuffer(unsigned int* indices, size_t size);
			virtual ~IndexBuffer();

			/* Methods */
			virtual void Bind() const override;
			virtual void Unbind() const override;
			
			/* Getters */
			inline const unsigned int GetId() { return m_ibo; }
			virtual inline const unsigned int GetCount() const override { return m_count; }

			void SetBufferData(const unsigned int* indices, size_t count);
			void SetBufferData(const std::vector<unsigned int> &indices);

		private:
			size_t m_count;
			unsigned int m_ibo;
	};
}}
