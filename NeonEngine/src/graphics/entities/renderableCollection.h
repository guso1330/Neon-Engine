#pragma once

#include "./model.h"

#include <glad/glad.h>
#include <vector>

/*
	Class that utilizes instanced rendering
*/
namespace neon {

	class RenderableCollection {
		public:
			RenderableCollection(Model *model, std::vector<Transform> &transforms);
			// void Submit();
			void Flush();

		private:
			void init();

		private:
			Model *m_model;

			std::vector<glm::mat4> m_transforms;
			glm::mat4 m_modelMatrix;
			GLuint m_vao, m_vbo, m_ibo, m_posvbo;
	};

}