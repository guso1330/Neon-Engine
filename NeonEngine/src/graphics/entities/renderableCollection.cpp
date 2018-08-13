#include "renderableCollection.h"
#include <math.h>

namespace neon {
	RenderableCollection::RenderableCollection(Renderable3d *renderable, Program *program) :
		m_renderable(renderable),
		m_program(program)

	{
		m_model = nullptr;
		m_vao = m_renderable->GetVao();

		Init();
	}

	RenderableCollection::RenderableCollection(Model *model, Program *program) :
		m_model(model),
		m_program(program)
	{
		m_renderable = nullptr;
		m_vao = m_model->GetVao();

		Init();
	}

	RenderableCollection::~RenderableCollection() {
		delete m_vbo;
	}

	// TODO: make the RenderableCollection not a static buffer, but dynamic
	void RenderableCollection::Init() {
		// m_modelMatrix = glm::mat4(1.0f);
		
		// // TODO: error handling on the m_transformLoc!
		// m_transformLoc = m_program->GetAttributeLocation("transform");
		// m_vbo = new VertexBuffer(BUFFER_SIZE);

		// m_layout.Push(VALUE_TYPE::MAT4, 4, 0 * sizeof(glm::vec4));
		// m_layout.Push(VALUE_TYPE::MAT4, 4, 1 * sizeof(glm::vec4));
		// m_layout.Push(VALUE_TYPE::MAT4, 4, 2 * sizeof(glm::vec4));
		// m_layout.Push(VALUE_TYPE::MAT4, 4, 3 * sizeof(glm::vec4));
		// m_vao->PushBuffer(m_vbo, m_layout, m_transformLoc);
		// m_vao->SetVertexAttribDivisors(m_transformLoc, m_transformLoc+3, 1);
	}

	// Todo: This performance could most likely be vastly improved
	void RenderableCollection::SetTransforms(std::vector<Transform> &n_transforms) {
		// m_transforms.clear();
		// for(int i=0; i<n_transforms.size(); ++i) {
		// 	m_transforms.push_back(n_transforms[i].GetModelMatrix());
		// }
		// HandleBufferData();
	}

	// Todo: This performance could most likely be vastly improved
	void RenderableCollection::UpdateAllTransforms(std::vector<Transform> &transforms, Transform &transform) {
		// m_transforms.clear();
		// for(int i=0; i < transforms.size(); ++i) {
		// 	m_transforms.push_back(transforms[i].GetModelMatrix() * transform.GetModelMatrix());
		// }
		// HandleBufferData();
	}

	void RenderableCollection::HandleBufferData() {
		// if(!(m_transforms.size() > (MAX_ELEMENTS * m_size_factor))) {
		// 	m_vbo->BufferData(m_transforms);
		// } else { // TODO: dynamically create buffers for mutliple draw calls if vbos get to large, just allocating more and more data
		// 	m_size_factor = (int)(ceil((double)m_transforms.size() / MAX_ELEMENTS));
		// 	delete m_vbo;
		// 	m_vbo = new VertexBuffer(BUFFER_SIZE * m_size_factor);
		// 	m_vao->DisableVertexAttribs(m_transformLoc, m_transformLoc+3);
		// 	m_vao->PushBuffer(m_vbo, m_layout, m_transformLoc);
		// 	m_vao->SetVertexAttribDivisors(m_transformLoc, m_transformLoc+3, 1);
		// 	m_vbo->BufferData(m_transforms);
		// }
	}

	void RenderableCollection::Draw() const {
		// m_program->Bind();
		// m_vao->Bind();
		
		// Transform t = m_renderable != nullptr ? m_renderable->GetTransform() : m_model->GetTransform();

		// if (m_renderable != nullptr) {
		// 	m_renderable->SetUpDraw(t.GetModelMatrix());
		// 	GL_Call(glDrawElementsInstanced(GL_TRIANGLES, m_renderable->GetIndexData().size(), GL_UNSIGNED_INT, NULL, m_transforms.size()));
		// 	m_renderable->UnSetDraw();
		// } else if (m_model != nullptr) {
		// 	m_model->GetIbo()->Bind();

		// 	Transform t = m_model->GetTransform();

		// 	for(int i=0; i < m_model->GetMeshes().size(); ++i) {

		// 		m_model->SetUpDraw(t.GetModelMatrix(), m_model->GetMeshes()[i]);

		// 		GL_Call(glDrawElementsInstancedBaseVertex(GL_TRIANGLES, m_model->GetMeshes()[i]->GetIndicesSize(), GL_UNSIGNED_INT, NULL,  m_transforms.size(), m_model->GetMeshes()[i]->GetIndex()));

		// 		m_model->UnSetDraw(m_model->GetMeshes()[i]);
		// 	}
		// }
	}
}