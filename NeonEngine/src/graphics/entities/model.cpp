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
		Init();
	}

	Model::~Model() { 
		delete m_mesh;
		delete m_ibo;
	}

	void Model::Init() {
		m_modelMatrix = glm::mat4(1.0f);
		m_color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);


		clock_t begin = std::clock();

		BuildVertexData();
		
		clock_t end = std::clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("Time of BuildVertexData: %lf\n\n", elapsed_secs);

		// PRINT DATA FROM BUILD VERTEX DATA
		// printf("VertexData\n");
		// for(std::vector<Vertex>::iterator it=m_vertexData.begin(); it != m_vertexData.end(); ++it) {
		// 	printf("%-16s, %-16s, %-16s\n", glm::to_string((*it).pos).c_str(), glm::to_string((*it).uv).c_str(), glm::to_string((*it).normal).c_str());
		// }
		
		// printf("Indices\n");
		// for(std::vector<unsigned int>::iterator it=m_indices.begin(); it != m_indices.end(); ++it) {
		// 	printf("%d\n", (*it));
		// }
		
		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(Vertex), &(*(m_vertexData.begin())), GL_STATIC_DRAW);

		cout << "VERTEX DATA SIZE: " << m_vertexData.size() << std::endl;
		cout << "INDICES SIZE: " << m_indices.size() << std::endl;

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)NULL);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(3 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		m_ibo = new IndexBuffer(m_indices);

		// TODO: Within .objloader, I need to create an array 
		// with all the unique vertices and then create an index
		// array that will index these vertices.

		// m_vao.AddBuffer(new VertexBuffer(m_mesh->GetVertices()), 0);
		// if(!m_mesh->GetUVs().empty()) {
		// 	m_vao.AddBuffer(new VertexBuffer(m_mesh->GetUVs()), 1);
		// }

		glBindVertexArray(0);
	}

	void Model::BuildVertexData() {
		std::vector<Index> indexSet;

		std::unordered_set<Index> index_set;
		// std::cout << "Indices size before: " << m_mesh->GetIndexObjSize() << std::endl;
		
		//
		// Build the unique indices
		//
		clock_t begin = std::clock();
		for(int i=0; i < (m_mesh->GetIndexObjSize()); ++i) {
			
			// Index c_index = m_mesh->GetIndexObj()[i];

			index_set.insert(m_mesh->GetIndexObj()[i]);
			
			// if (std::find(indexSet.begin(), indexSet.end(), m_mesh->GetIndexObj()[i]) == indexSet.end()) {
			// 	Index current_index = m_mesh->GetIndexObj()[i];
			// 	indexSet.push_back(current_index);
				
			// 	// Create a temporary vertex
			// 	Vertex temp_vertex;
				
			// 	// Grab the indices for the current_index
			// 	int pos_index, uv_index, normal_index;

			// 	// Will alwasy have_vi
			// 	if(current_index.has_vi) {
			// 		pos_index = current_index.vertex_index;
			// 		temp_vertex.pos = m_mesh->GetVertices()[pos_index];
			// 	}
			// 	if(current_index.has_ui) {
			// 		uv_index = current_index.uv_index;
			// 		temp_vertex.uv = m_mesh->GetUVs()[uv_index];
			// 	} else {
			// 		temp_vertex.uv = glm::vec2(0.0, 0.0);
			// 	}
			// 	if(current_index.has_ni) {
			// 		normal_index = current_index.normal_index;
			// 		temp_vertex.normal = m_mesh->GetNormals()[normal_index];
			// 	} else {
			// 		temp_vertex.normal = glm::vec3(0.0,0.0,0.0);
			// 	}

			// 	m_vertexData.push_back(temp_vertex);
			// }
		}
		clock_t end = std::clock();
		double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("Time of BuildVertexData 1st for loop: %lf\n\n", elapsed_secs);

		//
		// Build vertex data
		//
		for (std::unordered_set<Index>::iterator it=index_set.begin(); it!=index_set.end(); ++it) {
			Index c_index = (*it);
			// Create a temporary vertex
			Vertex temp_vertex;
			
			// Grab the indices for the current_index
			int pos_index, uv_index, normal_index;

			// Will alwasy have_vi
			if(current_index.has_vi) {
				pos_index = current_index.vertex_index;
				temp_vertex.pos = m_mesh->GetVertices()[pos_index];
			}
			if(current_index.has_ui) {
				uv_index = current_index.uv_index;
				temp_vertex.uv = m_mesh->GetUVs()[uv_index];
			} else {
				temp_vertex.uv = glm::vec2(0.0, 0.0);
			}
			if(current_index.has_ni) {
				normal_index = current_index.normal_index;
				temp_vertex.normal = m_mesh->GetNormals()[normal_index];
			} else {
				temp_vertex.normal = glm::vec3(0.0,0.0,0.0);
			}

			m_vertexData.push_back(temp_vertex);
		}

		begin = std::clock();
		//
		// Grab the index of each unique vertex
		//
		for (int i=0; i < (m_mesh->GetIndexObjSize()); ++i) {
			Index c_index = m_mesh->GetIndexObj()[i];

			Vertex search_vertex;

			/* Position - ALWAYS WILL HAVE VERTICES */
			if(c_index.has_vi) {
				search_vertex.pos = m_mesh->GetVertices()[c_index.vertex_index];
			}
			/* UVs */
			if(c_index.has_ui) {
				search_vertex.uv = m_mesh->GetUVs()[c_index.uv_index];
			} else {
				search_vertex.uv = glm::vec2(0.0, 0.0);
			}
			/* Normals */
			if(c_index.has_ni) {
				search_vertex.normal = m_mesh->GetNormals()[c_index.normal_index];
			} else {
				search_vertex.normal = glm::vec3(0.0,0.0,0.0);
			}

			int pos = std::find(m_vertexData.begin(), m_vertexData.end(), search_vertex) - m_vertexData.begin();
			m_indices.push_back(pos);
		}
		end = std::clock();
		elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
		printf("Time of BuildVertexData 2nd for loop: %lf\n\n", elapsed_secs);

		// DEBUG
		// for (std::vector<Vertex>::iterator it=m_vertexData.begin(); it!=m_vertexData.end(); ++it) {
		// 	printf("%-16s, %-16s, %-16s\n", glm::to_string((*it).pos).c_str(), glm::to_string((*it).uv).c_str(), glm::to_string((*it).normal).c_str());
		// }
		// printf("vector\n");
		// for (std::vector<Index>::iterator it=indexSet.begin(); it!=indexSet.end(); ++it) {
		// 	printf("%d, %d, %d\n", (*it).vertex_index, (*it).uv_index, (*it).normal_index);
		// }
		printf("\nunordered_set\n");
		for (std::unordered_set<Index>::iterator it=index_set.begin(); it!=index_set.end(); ++it) {
			printf("%d, %d, %d\n", (*it).vertex_index, (*it).uv_index, (*it).normal_index);
		}
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