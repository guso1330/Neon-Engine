#include "renderableCollection.h"

namespace neon {
	RenderableCollection::RenderableCollection(Renderable3d *renderable, std::vector<Transform> &transforms, Program *program) :
		m_renderable(renderable),
		m_program(program)

	{
		m_modelMatrix = glm::mat4(1.0f);
		m_vao = m_renderable->GetVao();

		for(int i=0; i < transforms.size(); ++i) {
			m_transforms.push_back(transforms[i].GetModelMatrix());
		}

		init();
	}

	// TODO: make the RenderableCollection not a static buffer, but dynamic
	void RenderableCollection::init() {
		GL_Call(glBindVertexArray(m_vao));

		// generate a VBO
		GL_Call(glGenBuffers(1, &m_vbo));
		
		// Bind the buffer object
		GL_Call(glBindBuffer(GL_ARRAY_BUFFER, m_vbo));
		GL_Call(glBufferData(GL_ARRAY_BUFFER, m_transforms.size() * sizeof(glm::mat4), &m_transforms.front() , GL_STATIC_DRAW));

		// set attribute pointers for matrix (4 times vec4)
		GL_Call(glEnableVertexAttribArray(2));
		GL_Call(glEnableVertexAttribArray(3));
		GL_Call(glEnableVertexAttribArray(4));
		GL_Call(glEnableVertexAttribArray(5));
		GL_Call(glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0));
		GL_Call(glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4))));
		GL_Call(glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4))));
		GL_Call(glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4))));

		GL_Call(glVertexAttribDivisor(2, 1));
		GL_Call(glVertexAttribDivisor(3, 1));
		GL_Call(glVertexAttribDivisor(4, 1));
		GL_Call(glVertexAttribDivisor(5, 1));

		GL_Call(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GL_Call(glBindVertexArray(0));
	}

	void RenderableCollection::Flush() {
		m_program->Bind();

		GL_Call(glBindVertexArray(m_vao));
		
		Transform t = m_renderable->GetTransform();
		m_renderable->SetUpDraw(t.GetModelMatrix());
		
		// std::cout << "indices: " << m_renderable->GetIndexData().size() << std::endl;
		GL_Call(glDrawElementsInstanced(GL_TRIANGLES, m_renderable->GetIndexData().size(), GL_UNSIGNED_INT, NULL, m_transforms.size()));

		m_renderable->UnSetDraw();

		m_program->Unbind();
	}
}