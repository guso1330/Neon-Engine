#pragma once

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include "../buffers/vertexArray.h"
#include "../buffers/vertexBuffer.h"
#include "../buffers/indexBuffer.h"
#include "./mesh.h"
#include "../../shaders/program.h"

namespace neon {
	class Model {
	public:
		Model(const char *filename, Program* program);
		~Model();

		inline Mesh* GetMesh() const { return m_mesh; }
		inline const glm::mat4 GetModelMatrix() const { return m_modelMatrix; }

		// Draw Functions
		void Draw() const;
	private:
		void Init();
	private:
		VertexArray m_vao;
		IndexBuffer *m_ibo;

		/* TODO: Might want to replace this with a require Model
		instead of a *Model*/
		Mesh *m_mesh;

		glm::mat4 m_modelMatrix;
		GLuint m_modelLoc;

		Program *m_program;
	};
}