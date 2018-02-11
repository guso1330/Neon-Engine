#include "renderableCollection.h"

namespace neon {
	RenderableCollection::RenderableCollection(Model *model, std::vector<Transform> &transforms) {
		m_modelMatrix = glm::mat4(1.0f);
		m_model = model;
		for(int i=0; i<transforms.size(); ++i) {
			m_transforms.push_back(transforms[i].GetModelMatrix());
		}

		init();
	}

	// TODO: make the RenderableCollection not a static buffer, but dynamic
	void RenderableCollection::init() {
		// glGenVertexArrays(1, &m_vao);
		
		
		// glBindVertexArray(m_vao);
		
		// glGenBuffers(1, &m_vbo);
		// glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		// glBufferData(GL_ARRAY_BUFFER, m_model->GetVertexData().size() * sizeof(Vertex), &(*(m_model->GetVertexData().begin())), GL_STATIC_DRAW);

		// glGenBuffers(1, &m_posvbo);
		// glBindBuffer(GL_ARRAY_BUFFER, m_posvbo);
		// glBufferData(GL_ARRAY_BUFFER, m_transforms.size() * sizeof(glm::vec3), m_transforms.begin(), GL_STREAM_DRAW);

		// printf("Size of m_vertexData: %lu bytes\n", m_vertexData.size() * sizeof(Vertex));
		// printf("Size of m_indicies: %lu bytes\n", m_indices.size() * sizeof(unsigned int));

		// glEnableVertexAttribArray(0);
		// glEnableVertexAttribArray(1);

		// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(struct Vertex, pos)));
		// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid*)(offsetof(struct Vertex, uv)));
		// glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof())

		// glBindBuffer(GL_ARRAY_BUFFER, 0);
		
		// m_ibo = new IndexBuffer(m_model->GetIndexData());

		// glBindVertexArray(0);
	}

	void RenderableCollection::Flush() {

	}
}