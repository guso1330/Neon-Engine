#pragma once

#include "Graphics/Renderers/BufferLayout.h"

namespace Neon {
	class IVertexBuffer {
		public:
			/* Constructors */
			virtual ~IVertexBuffer() = default;

			/* Methods */
			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			/* Getters */
			virtual const BufferLayout& GetLayout() const = 0;
			virtual BufferUsage GetUsage() const = 0;

			/* Setters */
			virtual void SetLayout(const BufferLayout& bufferLayout) = 0;

			static IVertexBuffer* Create(void* data, size_t size, const BufferLayout& bufferLayout);
	};
}
