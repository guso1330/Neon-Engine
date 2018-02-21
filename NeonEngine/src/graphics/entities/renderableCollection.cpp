#include "renderableCollection.h"

namespace neon {
	RenderableCollection::RenderableCollection(Renderable3d *renderable, std::vector<Transform> &transforms, Program *program) :
		m_renderable(renderable),
		m_program(program)

	{
		m_modelMatrix = glm::mat4(1.0f);
		m_vao = m_renderable->GetVao();

		for(int i=0; i < transforms.size(); ++i) {
			m_transforms.push_back(transforms[i].GetModelMatrix());
		}

		init();
	}

	RenderableCollection::~RenderableCollection() {
		delete m_vbo;
	}

	// TODO: make the RenderableCollection not a static buffer, but dynamic
	void RenderableCollection::init() {
		// GL_Call(glBindVertexArray(m_vao));
		m_vbo = new VertexBuffer(m_transforms);

		m_vao->Bind();

		// VertexBufferLayout layout;
		// layout.Push(VALUE_TYPE::FLOAT, 4);
		// layout.Push(VALUE_TYPE::FLOAT, 4);
		// layout.Push(VALUE_TYPE::FLOAT, 4);
		// layout.Push(VALUE_TYPE::FLOAT, 4);
		// m_vao->AddBuffer(m_vbo, layout, 2);

		// set attribute pointers for matrix (4 times vec4)
		GL_Call(glEnableVertexAttribArray(2));
		GL_Call(glEnableVertexAttribArray(3));
		GL_Call(glEnableVertexAttribArray(4));
		GL_Call(glEnableVertexAttribArray(5));
		GL_Call(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0));
		GL_Call(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4))));
		GL_Call(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4))));
		GL_Call(glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4))));

		GL_Call(glVertexAttribDivisor(2, 1));
		GL_Call(glVertexAttribDivisor(3, 1));
		GL_Call(glVertexAttribDivisor(4, 1));
		GL_Call(glVertexAttribDivisor(5, 1));
	}

	void RenderableCollection::Flush() {
		m_program->Bind();

		m_vao->Bind();
		
		Transform t = m_renderable->GetTransform();
		m_renderable->SetUpDraw(t.GetModelMatrix());
		
		GL_Call(glDrawElementsInstanced(GL_TRIANGLES, m_renderable->GetIndexData().size(), GL_UNSIGNED_INT, NULL, m_transforms.size()));

		m_renderable->UnSetDraw();

		m_program->Unbind();
	}
}