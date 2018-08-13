#pragma once

#include "../../../app/window.h"
#include "./GL_Error.h"
#include "./vertexArray.h"
#include "./vertexBuffer.h"
#include "./indexBuffer.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <iostream>

namespace neon {
	class OpenGLContext {
		public:
			// Constructor
			OpenGLContext();

			// Public Methods
			bool Init();
			void Clear() const;

			// Get Methods
			void CreateVao();

			// Set Methods
			void SetClearColor(float r, float g, float b, float a);

		private:
			glm::vec4 m_clearColor;

			std::map<unsigned int, VertexArray> m_vaoMap;
	};
}
