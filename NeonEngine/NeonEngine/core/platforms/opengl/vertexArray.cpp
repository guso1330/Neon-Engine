#include "./VertexArray.h"

#include "nepch.h"

namespace Neon { namespace OpenGL {
	VertexArray::VertexArray() {
		GL_Call(glGenVertexArrays(1, &m_vao));
	}

	VertexArray::~VertexArray() {
		GL_Call(glDeleteVertexArrays(1, &m_vao));
	}

	void VertexArray::Bind() const {
		GL_Call(glBindVertexArray(m_vao));
	}

	void VertexArray::Unbind() const {
		GL_Call(glBindVertexArray(0));
	}

	/*
		TODO
		- Update AddVertexBuffer and AddIndexBuffer to include setup functionality, this way you can abstract away that stuff from the renderer code?
	*/
	void VertexArray::AddVertexBuffer(std::shared_ptr<IVertexBuffer>& vb) {
		m_VertexBuffers.push_back(vb);
	}

	void VertexArray::AddIndexBuffer(std::shared_ptr<IIndexBuffer>& ib) {
		m_IndexBuffer = ib;
	}
}}
