#pragma once

#include "./GL_Error.h"
#include "Graphics/Renderers/IVertexBuffer.h"
#include "Graphics/Renderers/BufferLayout.h"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Neon { namespace OpenGL {
	static GLenum ConvertShaderDataTypeToOpenGLType(ShaderDataType type) {
		switch (type)
		{
			case ShaderDataType::BOOL: 	 return GL_BOOL;
			case ShaderDataType::FLOAT:  return GL_FLOAT;
			case ShaderDataType::FLOAT2: return GL_FLOAT;
			case ShaderDataType::FLOAT3: return GL_FLOAT;
			case ShaderDataType::FLOAT4: return GL_FLOAT;
			case ShaderDataType::INT: 	 return GL_INT;
			case ShaderDataType::INT2: 	 return GL_INT;
			case ShaderDataType::INT3: 	 return GL_INT;
			case ShaderDataType::INT4: 	 return GL_INT;
			case ShaderDataType::UINT:   return GL_UNSIGNED_INT;
			case ShaderDataType::UINT2:  return GL_UNSIGNED_INT;
			case ShaderDataType::UINT3:  return GL_UNSIGNED_INT;
			case ShaderDataType::UINT4:  return GL_UNSIGNED_INT;
			case ShaderDataType::MAT3: 	 return GL_FLOAT;
			case ShaderDataType::MAT4: 	 return GL_FLOAT;
			case ShaderDataType::NONE:   return GL_NONE;
		}

		NE_CORE_ASSERT(false, "ShaderDataType to OpenGL Type: Unknown ShaderDataType");
		return 0;
	}

	static GLenum ConvertBufferUsageToOpenGLUsage(BufferUsage type) {
		switch(type) {
			case BufferUsage::STATIC:  return GL_STATIC_DRAW;
			case BufferUsage::DYNAMIC: return GL_DYNAMIC_DRAW;
			case BufferUsage::NONE: 	  return GL_NONE;
			default: 			  break;
		}
		NE_CORE_ASSERT(false, "BufferUsage to OpenGL Usage: Unknown BufferUsage type");
		return 0;
	}

	class VertexBuffer : public IVertexBuffer {
		public:
			/* Constructors */
			VertexBuffer(BufferUsage usage = BufferUsage::STATIC);
			VertexBuffer(void* data, size_t size, const BufferLayout& bufferLayout);
			virtual ~VertexBuffer();

			/* Methods */
			virtual void Bind() const override;
			virtual void Unbind() const override;
			void Resize(size_t size);

			/* Getters */
			inline const unsigned int GetId() const { return m_vbo; }
			inline virtual const BufferLayout& GetLayout() const override { return m_layout; }
			inline virtual BufferUsage GetUsage() const override { return m_usage; }

			/* Setters */
			virtual void SetLayout(const BufferLayout& bufferLayout) override { m_layout = bufferLayout; }
			void SetBufferData(const void* data, size_t size);

		private:
			BufferLayout m_layout;
			BufferUsage m_usage;
			size_t m_size;
			unsigned int m_vbo;
	};
}}
