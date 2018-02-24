#include "renderableCollection.h"

namespace neon {
	RenderableCollection::RenderableCollection(Renderable3d *renderable, Program *program) :
		m_renderable(renderable),
		m_program(program)

	{
		m_modelMatrix = glm::mat4(1.0f);
		m_vao = m_renderable->GetVao();

		init();
	}

	RenderableCollection::~RenderableCollection() {
		delete m_vbo;
	}

	// TODO: make the RenderableCollection not a static buffer, but dynamic
	void RenderableCollection::init() {
		// GL_Call(glBindVertexArray(m_vao));
		m_vbo = new VertexBuffer(BUFFER_SIZE);

		m_layout.Push(VALUE_TYPE::MAT4, 4, 0 * sizeof(glm::vec4));
		m_layout.Push(VALUE_TYPE::MAT4, 4, 1 * sizeof(glm::vec4));
		m_layout.Push(VALUE_TYPE::MAT4, 4, 2 * sizeof(glm::vec4));
		m_layout.Push(VALUE_TYPE::MAT4, 4, 3 * sizeof(glm::vec4));
		m_vao->PushBuffer(m_vbo, m_layout, 2);

		GL_Call(glVertexAttribDivisor(2, 1));
		GL_Call(glVertexAttribDivisor(3, 1));
		GL_Call(glVertexAttribDivisor(4, 1));
		GL_Call(glVertexAttribDivisor(5, 1));
	}

	void RenderableCollection::SetTransforms(std::vector<Transform> &n_transforms) {
		m_transforms.clear();
		for(int i=0; i<n_transforms.size(); ++i) {
			m_transforms.push_back(n_transforms[i].GetModelMatrix());
		}
		m_vbo->BufferData(m_transforms);
	}

	// Todo: This performance could most likely be vastly improved
	void RenderableCollection::UpdateAllTransforms(std::vector<Transform> &transforms, Transform &transform) {
		m_transforms.clear();
		for(int i=0; i < transforms.size(); ++i) {
			m_transforms.push_back(transforms[i].GetModelMatrix() * transform.GetModelMatrix());
		}
		m_vbo->BufferData(m_transforms);
	}

	void RenderableCollection::Draw() {
		m_program->Bind();
		m_vao->Bind();
		
		Transform t = m_renderable->GetTransform();
		m_renderable->SetUpDraw(t.GetModelMatrix());
		
		GL_Call(glDrawElementsInstanced(GL_TRIANGLES, m_renderable->GetIndexData().size(), GL_UNSIGNED_INT, NULL, m_transforms.size()));

		m_renderable->UnSetDraw();
	}
}