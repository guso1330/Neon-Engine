#include "renderable3d.h"

namespace Neon {
	Renderable3d::Renderable3d() {
		// Default values
		m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		isDataSent = false;
		m_material = new Material();
	}

	Renderable3d::Renderable3d(Program* program) :
		m_program(program)
	{
		m_program->Bind();
		m_modelLoc = m_program->GetUniformLocation("model");
		m_colorLoc = m_program->GetUniformLocation("vcolor");
		m_normalMatrixLoc = m_program->GetUniformLocation("normal_matrix");

		// Default values
		m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		// Set the flags
		isDataSent = false;
		m_material = new Material();
	}

	Renderable3d::~Renderable3d() {
		delete m_vao;
		delete m_vbo;
		delete m_ibo;
	}

	void Renderable3d::SetTexture(const std::string &filename, TextureType type) {
		Texture* texture = new Texture(filename, type);

		switch(type) {
			case Diffuse:
				m_material->SetDiffuse(texture);
				break;
			case Specular:
				m_material->SetSpecular(texture);
				break;
			case Normal:
				break;
			case Height:
				break;
			case Occlusion:
				break;
			default:
				break;
		}		
	}

	void Renderable3d::SetTexture(Texture* n_texture, TextureType type) { 
		if(type == Diffuse) {
			m_material->SetDiffuse(n_texture);
		} else if (type == Specular) {
			m_material->SetSpecular(n_texture);
		}
	}

	void Renderable3d::SendVertexData() {
		// // Create VAO, VBO, and IBO
		// m_vao = new VertexArray();
		// m_vbo = new VertexBuffer();
		// m_ibo = new IndexBuffer();

		// m_vao->Bind();
		// m_vbo->Bind();
		// BufferLayout layout;
		// layout.Push(VALUE_TYPE::FLOAT, 3, offsetof(struct Vertex, pos));
		// layout.Push(VALUE_TYPE::FLOAT, 2, offsetof(struct Vertex, uv));
		// layout.Push(VALUE_TYPE::FLOAT, 3, offsetof(struct Vertex, normal));

		// m_vao->PushBuffer(m_vbo, layout);
	}

	void Renderable3d::SetUpDraw(const glm::mat4 &transform) const {
		// if(isDataSent) {
		// 	m_program->Bind();
		// 	m_vao->Bind();
		// 	m_ibo->Bind();

		// 	m_material->Bind(m_program);

		// 	m_program->SetUniform4f(m_colorLoc, m_color);
		// 	m_program->SetUniformMat4(m_modelLoc, transform);
		// 	m_program->SetUniformMat4(m_normalMatrixLoc, glm::transpose(glm::inverse(transform)));
		// }
	}

	void Renderable3d::UnSetDraw() const {
		// m_material->Unbind();
	}

	void Renderable3d::Draw() const {
		// this->SetUpDraw(m_transform.GetModelMatrix());
		// GL_Call(glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, NULL));
		// this->UnSetDraw();
	}

	void Renderable3d::Draw(const glm::mat4 &transform) const {
		// this->SetUpDraw(transform);
		// GL_Call(glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, NULL));
		// this->UnSetDraw();
	}
}