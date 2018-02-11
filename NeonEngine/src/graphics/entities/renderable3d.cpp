#include "renderable3d.h"

namespace neon {
	Renderable3d::Renderable3d(Program* program) :
		m_program(program)
	{
		m_modelLoc = program->GetUniformLocation("model");
		m_colorLoc = program->GetUniformLocation("vcolor");

		m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		m_texture = nullptr;

		// Set the flags
		isDataSent = false;
	}

	void Renderable3d::SetTexture(const char* filename) { m_texture = new Texture(filename); }

	void Renderable3d::SetTexture(Texture& n_texture) { m_texture = &n_texture; }

	void Renderable3d::SendVertexData() {
		
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(Vertex), &(*(m_vertexData.begin())), GL_STATIC_DRAW);

		printf("Size of m_vertexData: %lu bytes\n", m_vertexData.size() * sizeof(Vertex));
		printf("Size of m_indicies: %lu bytes\n", m_indices.size() * sizeof(unsigned int));

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(struct Vertex, pos)));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(struct Vertex, uv)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		m_ibo = new IndexBuffer(m_indices);

		glBindVertexArray(0);

		// TODO: should I be deleting this data?
		// m_vertexData.clear();
		// m_indices.clear();
	}

	void Renderable3d::Draw() const {
		if(isDataSent) {
			glBindVertexArray(m_vao);
			m_ibo->Bind();

			if(m_texture != nullptr) {
				m_texture->Bind(0);
				m_program->SetUniform1i("tex", 0);
			}

			m_program->SetUniform4f(m_colorLoc, m_color);
			m_program->SetUniformMat4(m_modelLoc, m_transform.GetModelMatrix());

			glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, NULL);

			if(m_texture != nullptr)
				m_texture->Unbind(0);

			m_ibo->Unbind();
			glBindVertexArray(0);
		}
	}

	void Renderable3d::Draw(glm::mat4 transform) const {
		if(isDataSent) {
			glBindVertexArray(m_vao);
			m_ibo->Bind();

			if(m_texture != nullptr) {
				m_texture->Bind(0);
				m_program->SetUniform1i("tex", 0);
			}

			m_program->SetUniform4f(m_colorLoc, m_color);
			m_program->SetUniformMat4(m_modelLoc, transform);

			glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, NULL);

			if(m_texture != nullptr)
				m_texture->Unbind(0);

			m_ibo->Unbind();
			glBindVertexArray(0);
		}	
	}
}