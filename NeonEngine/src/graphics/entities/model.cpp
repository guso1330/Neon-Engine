#include "model.h"

namespace neon {
	Model::Model(const char *filename, Program* program) : 
		Renderable3d(program)
	{
		m_mesh = new Mesh(filename);
		BuildVertexData();
		// TODO: need a method or something to run this
		//		 function only if you want to draw yourself
		SendVertexData();
	}

	Model::~Model() {}

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

		std::cout << "Size of m_vertexData: " << m_vertexData.size() << std::endl;
		std::cout << "Size of m_indices: " << m_indices.size() << std::endl;

		delete m_mesh;
	}
}