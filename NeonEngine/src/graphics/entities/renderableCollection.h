#pragma once

#include "./renderable3d.h"
#include "../../shaders/program.h"

#include <glad/glad.h>
#include <vector>
#include <iostream>

/*
	Class that utilizes instanced rendering
*/
namespace neon {

	class RenderableCollection {
		public:
			RenderableCollection(Renderable3d *renderable, std::vector<Transform> &transforms, Program *program);
			// void Submit();
			void Flush();

		private:
			void init();

		private:
			Program *m_program;
			
			Renderable3d *m_renderable;

			std::vector<glm::mat4> m_transforms;
			glm::mat4 m_modelMatrix;
			GLuint m_vao, m_vbo;
	};

}