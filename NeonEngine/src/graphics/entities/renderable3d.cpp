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
		m_texture = nullptr;

		// Set the flags
		isDataSent = false;
	}

	Renderable3d::~Renderable3d() {
		delete m_vao;
		delete m_vbo;
		delete m_ibo;
	}

	void Renderable3d::SetTexture(const char* filename) { m_texture = new Texture(filename); }

	void Renderable3d::SetTexture(Texture& n_texture) { m_texture = &n_texture; }

	void Renderable3d::SendVertexData() {

		printf("Size of m_vertexData: %lu bytes\n", m_vertexData.size() * sizeof(Vertex));
		printf("Size of m_indicies: %lu bytes\n", m_indices.size() * sizeof(unsigned int));

		// Create VAO, VBO, and IBO
		m_vao = new VertexArray();
		m_vbo = new VertexBuffer(m_vertexData);
		m_ibo = new IndexBuffer(m_indices);

		m_vao->Bind();
		m_vbo->Bind();
		

		GL_Call(glEnableVertexAttribArray(0));
		GL_Call(glEnableVertexAttribArray(1));

		
		GL_Call(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(struct Vertex, pos))));
		GL_Call(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(struct Vertex, uv))));
	}

	void Renderable3d::SetUpDraw(const glm::mat4 &transform) const {
		m_ibo->Bind();
		if(m_texture != nullptr) {
			m_texture->Bind(0);
			m_program->SetUniform1i("tex", 0);
		}

		m_program->SetUniform4f(m_colorLoc, m_color);
		m_program->SetUniformMat4(m_modelLoc, transform);
	}

	void Renderable3d::UnSetDraw() const {
		if(m_texture != nullptr)
			m_texture->Unbind(0);
	}	

	void Renderable3d::Draw() const {

		if(isDataSent) {
			m_program->Bind();
			m_vao->Bind();
			
			this->SetUpDraw(m_transform.GetModelMatrix());

			GL_Call(glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, NULL));

			this->UnSetDraw();
		}
	}

	void Renderable3d::Draw(glm::mat4 transform) const {

		if(isDataSent) {
			m_program->Bind();
			m_vao->Bind();

			this->SetUpDraw(transform);
			
			GL_Call(glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, NULL));

			this->UnSetDraw();
		}
	}
}