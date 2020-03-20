#include "./VertexArray.h"

#include "nepch.h"

namespace Neon { namespace OpenGL {
	VertexArray::VertexArray() {
		GL_Call(glGenVertexArrays(1, &m_vao));
	}

	VertexArray::~VertexArray() {
		Unbind();
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
		- Update AttachVertexBuffer and AttachIndexBuffer to include setup functionality, this way you can abstract away that stuff from the renderer code?
	*/
	void VertexArray::InitializeVertexBufferElements(std::shared_ptr<IVertexBuffer>& vb) {
		BufferLayout layout = vb->GetLayout();
		std::vector<BufferElement> elements = layout.GetElements();

		vb->Bind();

		for(size_t i = 0; i < elements.size(); ++i) {
			const auto& element = elements[i];
			GL_Call(glEnableVertexAttribArray(i));
			GL_Call(glVertexAttribPointer(
				i,
				element.GetComponentCount(),
				ConvertShaderDataTypeToOpenGLType(element.type),
				element.normalized, layout.GetStride(),
				(const void*)(element.offset)
			));
		}
	}

	void VertexArray::AttachVertexBuffer(std::shared_ptr<IVertexBuffer>& vb) {
		InitializeVertexBufferElements(vb);
		m_VertexBuffers.push_back(vb);
	}

	void VertexArray::AttachIndexBuffer(std::shared_ptr<IIndexBuffer>& ib) {
		m_IndexBuffer = ib;
	}

	void VertexArray::AttachVertexBuffer(std::shared_ptr<VertexBuffer>& vb) {
		std::shared_ptr<IVertexBuffer> b_vb = std::static_pointer_cast<IVertexBuffer>(vb);
		InitializeVertexBufferElements(b_vb);
		m_VertexBuffers.push_back(b_vb);
	}

	void VertexArray::AttachIndexBuffer(std::shared_ptr<IndexBuffer>& ib) {
		std::shared_ptr<IIndexBuffer> b_ib = std::static_pointer_cast<IIndexBuffer>(ib);
		m_IndexBuffer = b_ib;
	}
}}
