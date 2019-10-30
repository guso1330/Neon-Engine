#pragma once

#include "./GL_Error.h"
#include "Graphics/Renderers/IVertexBuffer.h"
#include "Graphics/Renderers/BufferLayout.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Neon { namespace OpenGL {
	class VertexBuffer : public IVertexBuffer {
		public:
			/* Constructors */
			VertexBuffer(unsigned int usage);
			virtual ~VertexBuffer();

			/* Methods */
			virtual void Bind() const override;
			virtual void Unbind() const override;
			void Resize(size_t size);

			/* Getters */
			inline const unsigned int GetId() const { return m_vbo; }
			virtual const BufferLayout& GetLayout() const override { return m_layout; }

			/* Setters */
			virtual void SetLayout(const BufferLayout& bufferLayout) override;
			void SetBufferData(const void* data, size_t size) const;

		private:
			BufferLayout m_layout;
			unsigned int m_usage;
			size_t m_size;
			unsigned int m_vbo;
	};
}}
