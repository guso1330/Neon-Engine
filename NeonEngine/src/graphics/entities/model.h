#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
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

		// GETTERS
		inline const Mesh* GetMesh() const { return m_mesh; }
		inline const glm::mat4& GetModelMatrix() const { return m_modelMatrix; }
		inline void SetModelMatrix(const glm::mat4 &n_modelMatrix) { m_modelMatrix = n_modelMatrix; }
		inline void SetColor(const glm::vec4 &n_color) { m_color = n_color; }

		// Draw Functions
		void Draw() const;

	private:
		void Init();
	
	private:
		VertexArray m_vao;
		IndexBuffer *m_ibo;
		Program *m_program;

		/* 
			TODO: Maybe I shouldn't declare this on the heap...?
		*/
		Mesh *m_mesh;

		glm::mat4 m_modelMatrix;
		GLuint m_modelLoc;
		GLuint m_colorLoc;
		
		glm::vec4 m_color;
	};
}