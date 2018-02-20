#pragma once

#include "./renderable3d.h"
#include "../../shaders/program.h"
#include "../buffers/vertexArray.h"
#include "../buffers/vertexBuffer.h"

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
			~RenderableCollection();
			void Flush();

		private:
			void init();

		private:
			Program *m_program;			
			Renderable3d *m_renderable;
			VertexArray *m_vao;
			VertexBuffer *m_vbo;

			std::vector<glm::mat4> m_transforms;
			glm::mat4 m_modelMatrix;

	};
}