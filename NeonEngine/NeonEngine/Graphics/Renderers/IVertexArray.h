#pragma once

#include "Graphics/Renderers/IVertexBuffer.h"
#include "Graphics/Renderers/IIndexBuffer.h"

#include "nepch.h"

namespace Neon  {
	class IVertexArray {
		public:
			/* Constructors */
			virtual ~IVertexArray() = default;

			/* Methods */
			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
			virtual void AddVertexBuffer(std::shared_ptr<IVertexBuffer>& vb) = 0;
			virtual void AddIndexBuffer(std::shared_ptr<IIndexBuffer>& ib) = 0;

			/* Getters */
			virtual const std::vector<std::shared_ptr<IVertexBuffer> >& GetVertexBuffers() const = 0;
			virtual const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const = 0;

			static IVertexArray* Create();
	};
}
