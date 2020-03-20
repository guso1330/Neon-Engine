#pragma once

#include "Graphics/Renderers/IVertexArray.h"
#include "Core/Platforms/OpenGL/GL_Error.h"
#include "Core/Platforms/OpenGL/VertexBuffer.h"
#include "Core/Platforms/OpenGL/IndexBuffer.h"

#include <glad/glad.h>

namespace Neon { namespace OpenGL {
	class VertexArray : public IVertexArray {
		public:
			VertexArray();
			virtual ~VertexArray();

			/* Methods */
			virtual void Bind() const override;
			virtual void Unbind() const override;
			virtual void AttachVertexBuffer(std::shared_ptr<IVertexBuffer>& vb) override;
			virtual void AttachIndexBuffer(std::shared_ptr<IIndexBuffer>& ib) override;
			void AttachVertexBuffer(std::shared_ptr<VertexBuffer>& vb);
			void AttachIndexBuffer(std::shared_ptr<IndexBuffer>& ib);

			/* Getters */
			inline const unsigned int GetVao() const { return m_vao; }
			virtual inline const std::vector<std::shared_ptr<IVertexBuffer> >& GetVertexBuffers() const override { return m_VertexBuffers; }
			virtual inline const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

		private:
			void InitializeVertexBufferElements(std::shared_ptr<IVertexBuffer>& vb);

		private:
			unsigned int m_vao;
			std::vector<std::shared_ptr<IVertexBuffer> > m_VertexBuffers;
			std::shared_ptr<IIndexBuffer> m_IndexBuffer;
	};
}}
