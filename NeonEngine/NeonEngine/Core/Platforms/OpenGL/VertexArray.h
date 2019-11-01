#pragma once

#include "./GL_Error.h"
#include "Graphics/Renderers/IVertexArray.h"

#include <glad/glad.h>

namespace Neon { namespace OpenGL {
	class VertexArray : public IVertexArray {
		public:
			VertexArray();
			~VertexArray();

			/* Methods */
			virtual void Bind() const override;
			virtual void Unbind() const override;
			virtual void AddVertexBuffer(std::shared_ptr<IVertexBuffer>& vb) override;
			virtual void AddIndexBuffer(std::shared_ptr<IIndexBuffer>& ib) override;

			/* Getters */
			inline const unsigned int GetVao() const { return m_vao; }
			virtual inline const std::vector<std::shared_ptr<IVertexBuffer> >& GetVertexBuffers() const override { return m_VertexBuffers; }
			virtual inline const std::shared_ptr<IIndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

		private:
			unsigned int m_vao;
			std::vector<std::shared_ptr<IVertexBuffer> > m_VertexBuffers;
			std::shared_ptr<IIndexBuffer> m_IndexBuffer;
	};
}}
