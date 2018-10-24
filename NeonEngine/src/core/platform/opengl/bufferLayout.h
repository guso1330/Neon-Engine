#pragma once

#include "./GL_Error.h"
#include "../../../graphics/entities/vertex.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

namespace neon {
	enum VALUE_TYPE {
		FLOAT 		  = 0,
		UNSIGNED_INT  = 1,
		UNSIGNED_BYTE = 2,
		VEC2		  = 4,
		VEC3		  = 5,
		VEC4		  = 6,
		MAT4		  = 7
	};

	struct BufferElements {
		unsigned int type;
		unsigned int size;
		unsigned int count;
		unsigned int offset;
		unsigned char normalized;
	};

	class BufferLayout {
		private:
			std::vector<BufferElements> m_layout;
			unsigned int m_stride;
			void Push(unsigned int type, unsigned int size, unsigned int count, unsigned int offset, unsigned char normalized) {
				m_layout.push_back({
					type,
					size,
					count,
					offset,
					normalized
				});
				m_stride += count * size;
			}
		public:
			BufferLayout() :
				m_stride(0)
			{}

			void Push(VALUE_TYPE value, unsigned int count, unsigned int offset, unsigned int length = 1) {
				switch(value) {
					case VALUE_TYPE::FLOAT:
						Push(GL_FLOAT, length * sizeof(float), count, offset, GL_FALSE);
						break;
					case VALUE_TYPE::UNSIGNED_INT:
						Push(GL_FLOAT, length * sizeof(unsigned int), count, offset, GL_FALSE);
						break;
					case VALUE_TYPE::UNSIGNED_BYTE:
						Push(GL_UNSIGNED_BYTE, length * sizeof(unsigned char), count, offset, GL_TRUE);
						break;
					case VALUE_TYPE::VEC2:
						Push(GL_FLOAT, length * sizeof(float), count, offset, GL_FALSE);
						break;
					case VALUE_TYPE::VEC3:
						Push(GL_FLOAT, length * sizeof(float), count, offset, GL_FALSE);
						break;
					case VALUE_TYPE::VEC4:
						Push(GL_FLOAT, length * sizeof(float), count, offset, GL_FALSE);
						break;
					case VALUE_TYPE::MAT4:
						Push(GL_FLOAT, length * sizeof(glm::mat4), count, offset, GL_FALSE);
						break;
				}
			}

			inline const std::vector<BufferElements> &GetLayout() const { return m_layout; }
			inline const unsigned int GetStride() const { return m_stride; }
	};
}