#pragma once

#include "../../engine/GL_Error.h"
#include "../entities/vertex.h"

#include <glad/glad.h>
#include <vector>

#define NEON_VERTEX_POS 0x911E
#define NEON_VERTEX_UV 0x9127

namespace neon {
	enum VALUE_TYPE {
		FLOAT 		  = 0,
		UNSIGNED_INT  = 1,
		UNSIGNED_BYTE = 2,
		VERTEX 		  = 3,
		// VEC2		  = 4,
		// VEC3		  = 5,
		// VEC4		  = 6,
		// MAT4		  = 7
	};

	struct VertexBufferElement {
		unsigned int type;
		unsigned int count;
		unsigned char normalized;
		enum VALUE_TYPE value_type;

		static unsigned int GetSizeOfType(unsigned int type) {
			switch(type) {
				case GL_FLOAT: 			return sizeof(float);
				case GL_UNSIGNED_INT: 	return sizeof(unsigned int);
				case GL_UNSIGNED_BYTE: 	return sizeof(unsigned char);
			}
			NEON_ASSERT(false);
			return 0;
		}

		static unsigned int GetOffsetOfType(enum VALUE_TYPE type, unsigned int count) {
			switch(type) {
				case VALUE_TYPE::FLOAT: 			return count * GetSizeOfType(GL_FLOAT);
				case VALUE_TYPE::UNSIGNED_INT: 		return count * GetSizeOfType(GL_UNSIGNED_BYTE);
				case VALUE_TYPE::UNSIGNED_BYTE: 	return count * GetSizeOfType(GL_UNSIGNED_INT);
				case VALUE_TYPE::VERTEX:			return count;
			}
			NEON_ASSERT(false);
			return 0;
		}
	};

	class VertexBufferLayout {
		public:
			VertexBufferLayout() :
				m_stride(0)
			{}

			void Push(VALUE_TYPE value, unsigned int count) {
				switch(value) {				
					case VALUE_TYPE::FLOAT:
						m_elements.push_back({
							GL_FLOAT,
							count,
							GL_FALSE,
							FLOAT
						});
						m_stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
						break;
					case VALUE_TYPE::UNSIGNED_INT:
						m_elements.push_back({
							GL_UNSIGNED_INT,
							count,
							GL_FALSE,
							UNSIGNED_INT
						});
						m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
						break;
					case VALUE_TYPE::UNSIGNED_BYTE:
						m_elements.push_back({
							GL_UNSIGNED_BYTE,
							count,
							GL_TRUE,
							UNSIGNED_BYTE
						});
						m_stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
						break;
					case VALUE_TYPE::VERTEX:
						m_elements.push_back({
							GL_FLOAT,
							count,
							GL_FALSE,
							VERTEX
						});
						m_stride += sizeof(Vertex);
						break;
				}
			}

			inline const std::vector<VertexBufferElement> &GetElements() const { return m_elements; }
			inline unsigned int GetStride() const { return m_stride; }

		private:
			std::vector<VertexBufferElement> m_elements;
			unsigned int m_stride;
	};
}