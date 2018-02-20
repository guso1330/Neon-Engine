#pragma once

#include "../../engine/GL_Error.h"
#include "../entities/vertex.h"

#include <glad/glad.h>
#include <vector>

#define NEON_VERTEX_POS 0x911E
#define NEON_VERTEX_UV 0x9127

namespace neon {
	struct VertexBufferElement {
		// unsigned int type;
		// unsigned int count;
		// unsigned char normalized;

		// static unsigned int GetSizeOfType(unsigned int type) {
		// 	switch(type) {
		// 		case GL_FLOAT: 			return 4;
		// 		case GL_UNSIGNED_INT: 	return 4;
		// 		case GL_UNSIGNED_BYTE: 	return 1;
		// 	}
		// 	NEON_ASSERT(false);
		// 	return 0;
		// }

		// static unsigned int GetOffsetOfType(unsigned int type, unsigned int count) {
		// 	switch(type) {
		// 		case GL_FLOAT: 			return count * 4;
		// 		case GL_UNSIGNED_INT: 	return count * 4;
		// 		case GL_UNSIGNED_BYTE: 	return count * 1;
		// 		case NEON_VERTEX_POS: 	return (offsetof(struct neon::Vertex, pos));
		// 		case NEON_VERTEX_UV:	return (offsetof(struct neon::Vertex, uv));
		// 	}
		// 	NEON_ASSERT(false);
		// 	return 0;
		// }
	};

	class VertexBufferLayout {
		public:
			VertexBufferLayout() :
				m_stride(0)
			{}

		// 	// todo: read up on why this works
		// 	// 
		// 	// Is this the generic type if you enter an invalid
		// 	// type that isn't supported?
		// 	template<typename T>
		// 	void Push(int count) {
		// 		static_assert(false);
		// 	}

		// 	template<>
		// 	void Push<float>(int count) {
		// 		m_elements.push_back({
		// 			GL_FLOAT,
		// 			count,
		// 			GL_FALSE
		// 		});
		// 		m_stride += VertexBufferElement::GetSizeOfType(GL_FLOAT);
		// 	}

		// 	template<>
		// 	void Push<unsigned int>(int count) {
		// 		m_elements.push_back({
		// 			GL_UNSIGNED_INT,
		// 			count,
		// 			GL_FALSE
		// 		});
		// 		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
		// 	}

		// 	template<>
		// 	void Push<unsigned char>(int count) {
		// 		m_elements.push_back({
		// 			GL_UNSIGNED_BYTE,
		// 			count,
		// 			GL_TRUE
		// 		});
		// 		m_stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
		// 	}

		// 	template<>
		// 	void Push<neon::Vertex>(int count) {
		// 		m_elements.push_back({
		// 			GL_FLOAT,
		// 			count,
		// 			GL_FALSE
		// 		});
		// 		m_stide += sizeof(neon::Vertex);
		// 	}

		// 	inline const std::vector<VertexBufferElement> &GetElements() const { return m_elements; }
		// 	inline unsigned int GetStride() const { return m_stride; }

		private:
			std::vector<VertexBufferElement> m_elements;
			unsigned int m_stride;
	};
}