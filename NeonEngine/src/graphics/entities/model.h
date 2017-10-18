#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "../buffers/vertexArray.h"
#include "../buffers/vertexBuffer.h"
#include "../buffers/indexBuffer.h"
#include "./mesh.h"

namespace neon {
	class Model {
		public:
			Model(const char *filename);
			~Model();

			inline Mesh* GetMesh() const { return m_mesh; }

			// Draw Functions
			void Draw() const;
		private:
			void Init();
		private:
			/* TODO: Might want to replace this with a require Model
			   instead of a *Model*/
			Mesh *m_mesh;
			glm::mat4 m_modelMatrix;
			VertexArray m_vao;
			IndexBuffer *m_ibo;
	};
}