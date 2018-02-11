#include "forwardRenderer.h"

namespace neon {
	ForwardRenderer::ForwardRenderer() {
		Init();
	}
	ForwardRenderer::~ForwardRenderer() {
		delete m_ibo;
		glDeleteBuffers(1, &m_vbo);
	}
	void ForwardRenderer::Init() {

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_TEX_INDEX);
		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_TEX_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	void ForwardRenderer::Begin() {

	}
	void ForwardRenderer::End() {
		
	}
	void ForwardRenderer::Submit(Renderable3d* renderable) {
		m_vertexData.insert(m_vertexData.begin(), renderable->GetVertexData().begin(), renderable->GetVertexData().end());
	}
	void ForwardRenderer::Flush() {
		
	}
}