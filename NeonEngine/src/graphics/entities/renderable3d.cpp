#include "renderable3d.h"

namespace neon {
	Renderable3d::Renderable3d(Program* program) :
		m_program(program)
	{
		m_program->Bind();
		m_modelLoc = m_program->GetUniformLocation("model");
		m_colorLoc = m_program->GetUniformLocation("vcolor");

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
		if(type == Diffuse) {
			m_material->diffuse = texture;
		} else if (type == Specular) {
			m_material->specular = texture;
		}
	}

	void Renderable3d::SetTexture(Texture* n_texture, TextureType type) { 
		if(type == Diffuse) {
			m_material->diffuse = n_texture;
		} else if (type == Specular) {
			m_material->specular = n_texture;
		}
	}

	void Renderable3d::SendVertexData() {

		printf("Size of m_vertexData: %lu bytes\n", m_vertexData.size() * sizeof(Vertex));
		printf("Size of m_indicies: %lu bytes\n\n", m_indices.size() * sizeof(unsigned int));

		// Create VAO, VBO, and IBO
		m_vao = new VertexArray();
		m_vbo = new VertexBuffer(m_vertexData);
		m_ibo = new IndexBuffer(m_indices);

		m_vao->Bind();
		m_vbo->Bind();
		VertexBufferLayout layout;
		layout.Push(VALUE_TYPE::VERTEX, 3, offsetof(struct Vertex, pos));
		layout.Push(VALUE_TYPE::VERTEX, 2, offsetof(struct Vertex, uv));
		layout.Push(VALUE_TYPE::VERTEX, 3, offsetof(struct Vertex, normal));

		m_vao->PushBuffer(m_vbo, layout);
	}

	void Renderable3d::SetUpDraw(const glm::mat4 &transform) const {
		if(isDataSent) {
			m_program->Bind();
			m_vao->Bind();
			m_ibo->Bind();

			m_material->Bind(m_program);

			m_program->SetUniform4f(m_colorLoc, m_color);
			m_program->SetUniformMat4(m_modelLoc, transform);

			GL_Call(glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, NULL));
		}
	}

	void Renderable3d::UnSetDraw() const {
		m_material->Unbind();
	}

	void Renderable3d::Draw() const {
		this->SetUpDraw(m_transform.GetModelMatrix());
		this->UnSetDraw();
	}

	void Renderable3d::Draw(const glm::mat4 &transform) const {
		this->SetUpDraw(transform);
		this->UnSetDraw();
	}
}