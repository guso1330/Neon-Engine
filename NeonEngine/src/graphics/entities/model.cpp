#include "model.h"
#include <ctime>
namespace neon {
	Model::Model(const char *filename, Program* program) :
		m_program(program)
	{
		m_mesh = new Mesh(filename);
		m_modelLoc = program->GetUniformLocation("model");
		m_colorLoc = program->GetUniformLocation("vcolor");
		m_texture = nullptr;
		m_modelMatrix = glm::mat4(1.0f);
		m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

		Init();
	}

	Model::~Model() { 
		delete m_ibo;
	}

	void Model::Init() {

		// Build the VertexData
		clock_t begin = std::clock();
		BuildVertexData();
		clock_t end = std::clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("Time of BuildVertexData: %lf\n\n", elapsed_secs);
		
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
	}

	void Model::BuildVertexData() {
		std::unordered_set<Index> index_set;
		
		/*****************************/
		/* Build the unique indices */
		/*****************************/
		clock_t begin = std::clock();
		int index = 0;
		for(int i=0; i < (m_mesh->GetIndexObjSize()); ++i) {
			Index n_index, c_index = m_mesh->GetIndexObj()[i];
			n_index.vertex_index = c_index.vertex_index;
			n_index.uv_index = c_index.uv_index;
			n_index.normal_index = c_index.normal_index;
			n_index.has_vi = c_index.has_vi;
			n_index.has_ui = c_index.has_ui;
			n_index.has_ni = c_index.has_ni;

			std::unordered_set<Index>::iterator index_exists = index_set.find(n_index);
			if(index_exists == index_set.end()) {
				n_index.index = index;
				index_set.insert(n_index);
				index++;
			}
		}
		clock_t end = std::clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("Time of BuildVertexData 1st for loop: %lf\n", elapsed_secs);

		begin = std::clock();
		/*********************/
		/* Build vertex data */
		/*********************/
		m_vertexData.resize(index_set.size());
		for (std::unordered_set<Index>::iterator it=index_set.begin(); it!=index_set.end(); ++it) {
			Index c_index = (*it);

			// Create a temporary vertex
			Vertex temp_vertex;
			// Grab the indices for the current_index
			int pos_index, uv_index, normal_index;

			// Will alwasy have_vi
			if(c_index.has_vi) {
				pos_index = c_index.vertex_index;
				temp_vertex.pos = m_mesh->GetVertices()[pos_index];
			}
			if(c_index.has_ui) {
				uv_index = c_index.uv_index;
				temp_vertex.uv = m_mesh->GetUVs()[uv_index];
			} else {
				temp_vertex.uv = glm::vec2(0.0, 0.0);
			}
			if(c_index.has_ni) {
				normal_index = c_index.normal_index;
				temp_vertex.normal = m_mesh->GetNormals()[normal_index];
			} else {
				temp_vertex.normal = glm::vec3(0.0,0.0,0.0);
			}
			m_vertexData[c_index.index] = temp_vertex;
		}
		end = std::clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("Time of BuildVertexData 2nd for loop: %lf\n", elapsed_secs);

		begin = std::clock();

		/****************************************/
		/* Grab the index of each unique vertex */
		/****************************************/
		for (int i=0; i < (m_mesh->GetIndexObjSize()); ++i) {
			Index c_index = m_mesh->GetIndexObj()[i];
			// find the index
			std::unordered_set<Index>::iterator found = index_set.find(c_index);
			m_indices.push_back((*found).index);
		}
		end = std::clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("Time of BuildVertexData 3rd for loop: %lf\n", elapsed_secs);

		// Delete the mesh
		delete m_mesh;
	}

	void Model::SetTexture(const char* filename) {
		m_texture = new Texture(filename);
	}

	void Model::Draw() const {
		glBindVertexArray(m_vao);
		m_ibo->Bind();

		if(m_texture != nullptr) {
			m_texture->Bind(0);
			m_program->SetUniform1i("tex", 0);
		}

		m_program->SetUniform4f(m_colorLoc, m_color);
		m_program->SetUniformMat4(m_modelLoc, m_modelMatrix);

		glDrawElements(GL_TRIANGLES, m_ibo->GetCount(), GL_UNSIGNED_INT, NULL);

		if(m_texture != nullptr)
			m_texture->Unbind(0);
		
		m_ibo->Unbind();
		glBindVertexArray(0);
	}
}