#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include "../buffers/vertexArray.h"
#include "../buffers/"

namespace neon {

	struct VertexData {
		glm::vec3 vertex;
		glm::vec2 text_coord;
	}

	class Renderable {
		protected:
			VertexArray *m_VAO;
			IndexBuffer *m_IBO;
			
		public: 
			Renderable();
			~Renderable();

	};
}