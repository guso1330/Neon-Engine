#pragma once

#include "nepch.h"

#include "Core/Core.h"

namespace Neon {

	/* 
		Shader Data Type
		TODO: Abstract this out to Core/Types?
	*/
	enum class ShaderDataType {
		NONE = 0,
		BOOL,
		FLOAT,
		FLOAT2,
		FLOAT3,
		FLOAT4,
		INT,
		INT2,
		INT3,
		INT4,
		UINT,
		UINT2,
		UINT3,
		UINT4,
		MAT3,
		MAT4,
	};

	static uint32_t GetShaderDataTypeSize(ShaderDataType type) {
		switch (type) {
			case ShaderDataType::BOOL:   return 1;
			case ShaderDataType::FLOAT:  return 4;
			case ShaderDataType::FLOAT2: return 4 * 2;
			case ShaderDataType::FLOAT3: return 4 * 3;
			case ShaderDataType::FLOAT4: return 4 * 4;
			case ShaderDataType::INT:    return 4;
			case ShaderDataType::INT2:   return 4 * 2;
			case ShaderDataType::INT3:   return 4 * 3;
			case ShaderDataType::INT4:   return 4 * 4;
			case ShaderDataType::UINT:   return 4;
			case ShaderDataType::UINT2:  return 4 * 2;
			case ShaderDataType::UINT3:  return 4 * 3;
			case ShaderDataType::UINT4:  return 4 * 4;
			case ShaderDataType::MAT3:   return 4 * 3 * 3;
			case ShaderDataType::MAT4:   return 4 * 4 * 4;
			case ShaderDataType::NONE:   break;
		}

		NE_CORE_ASSERT(false, "BufferLayout (GetShaderDataTypeSize): Type submitted isn't defined");
		return 0;
	}

	/* BufferElement */
	struct BufferElement {
		BufferElement() {}

		BufferElement(const std::string& n_name, ShaderDataType n_type, bool n_normalized = false) :
			name(n_name),
			type(n_type),
			size(GetShaderDataTypeSize(n_type)),
			offset(0),
			normalized(n_normalized)
		{}

		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized;

		uint32_t GetComponentCount() const {
			switch (type) {
				case ShaderDataType::BOOL:   return 1;
				case ShaderDataType::FLOAT:  return 1;
				case ShaderDataType::FLOAT2: return 2;
				case ShaderDataType::FLOAT3: return 3;
				case ShaderDataType::FLOAT4: return 4;
				case ShaderDataType::INT:    return 1;
				case ShaderDataType::INT2:   return 2;
				case ShaderDataType::INT3:   return 3;
				case ShaderDataType::INT4:   return 4;
				case ShaderDataType::UINT:   return 1;
				case ShaderDataType::UINT2:  return 2;
				case ShaderDataType::UINT3:  return 3;
				case ShaderDataType::UINT4:  return 4;
				case ShaderDataType::MAT3:   return 3 * 3;
				case ShaderDataType::MAT4:   return 4 * 4;
				case ShaderDataType::NONE:   break;
			}

			NE_CORE_ASSERT(false, "BufferLayout (GetComponentCount): Type submitted isn't defined");
			return 0;
		}
	};

	/* 
		BufferLayout
		TODO
			- Add support for initialization list like the cherno
	*/
	class BufferLayout {
		public:
			BufferLayout() :
				m_stride(0)
			{}

			BufferLayout(const std::initializer_list<BufferElement>& elements) : 
				m_elements(elements)
			{
				m_stride = 0;
				CalculateOffsetsAndStride();
			}

			/* Methods */
			void Push(const std::string& name, ShaderDataType type, uint32_t offset, bool normalized = false) {
				BufferElement n_buffer(name, type, normalized);
				n_buffer.offset = offset;
				Push(n_buffer);
			}

			/* Getters */
			inline const std::vector<BufferElement>& GetElements() const { return m_elements; }
			inline const uint32_t GetStride() const { return m_stride; }

			/* Accessors */
			std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
			std::vector<BufferElement>::iterator end() { return m_elements.end(); }
			std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
			std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }
		private:
			void Push(BufferElement& element) {
				m_elements.push_back(element);
				m_stride += element.GetComponentCount() * element.size;
			}
			void CalculateOffsetsAndStride() {
				uint32_t offset = 0;
				for (std::vector<BufferElement>::iterator it = m_elements.begin(); it != m_elements.end(); ++it) {
					(*it).offset = offset;
					offset += (*it).size;
					m_stride += (*it).size;
				}
			}
		private:
			uint32_t m_stride;
			std::vector<BufferElement> m_elements;
	};
}
