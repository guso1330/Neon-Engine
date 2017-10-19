#include "model.h"

namespace neon {
	Model::Model(const char *filename, Program* program) :
		m_program(program)
	{
		m_mesh = new Mesh(filename);
		m_modelLoc = program->GetUniformLocation("model");
		Init();
	}

	Model::~Model() { 
		delete m_mesh;
		delete m_ibo;
	}

	void Model::Init() {
		m_modelMatrix = glm::mat4(1.0f);
		m_ibo = new IndexBuffer(m_mesh->GetIndices());
		m_vao.AddBuffer(new VertexBuffer(m_mesh->GetVertices()), 0);
	}

	void Model::Draw() const {
		m_vao.Bind();
		m_ibo->Bind();

		m_program->SetUniformMat4(m_modelLoc, m_modelMatrix);
		glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, 0);
		
		m_ibo->Unbind();
		m_vao.Unbind();
	}
}