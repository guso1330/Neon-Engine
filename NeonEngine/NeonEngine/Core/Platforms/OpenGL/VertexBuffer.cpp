#include "./VertexBuffer.h"

#include "Core/Core.h"

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
			case ShaderDataType::NONE:   break;
		}

		NE_CORE_ASSERT(false, "ShaderDataType to OpenGL Type: Unknown ShaderDataType");
		return 0;
	}

	VertexBuffer::VertexBuffer(unsigned int usage)
		: m_usage(usage)
	{
		// Generate a new buffer
		GL_Call(glGenBuffers(1, &m_vbo));
	}

	VertexBuffer::~VertexBuffer() { 
		GL_Call(glDeleteBuffers(1, &m_vbo));
	}

	void VertexBuffer::Bind() const {
		GL_Call(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
	}

	void VertexBuffer::Unbind() const {
		GL_Call(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}

	void VertexBuffer::Resize(size_t size) {
		m_size = size;
		GL_Call(glBufferData(GL_ARRAY_BUFFER, size, NULL, m_usage));
	}

	void VertexBuffer::SetLayout(const BufferLayout& bufferLayout) {
		m_layout = bufferLayout;
		const auto& layout = m_layout.GetElements();
		for(size_t i = 0; i < layout.size(); ++i) {
			const auto& element = layout[i];
			GL_Call(glEnableVertexAttribArray(i));
			GL_Call(glVertexAttribPointer(i, element.GetComponentCount(), ConvertShaderDataTypeToOpenGLType(element.type), element.normalized, m_layout.GetStride(), (const void*)(element.offset)));
		}
	}

	void VertexBuffer::SetBufferData(const void* data, size_t size) const {
		GL_Call(glBufferData(GL_ARRAY_BUFFER, size, data, m_usage));
	}
}}
