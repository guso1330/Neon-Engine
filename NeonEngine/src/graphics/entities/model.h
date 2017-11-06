#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../buffers/vertexArray.h"
#include "../buffers/vertexBuffer.h"
#include "../buffers/indexBuffer.h"
#include "../../shaders/program.h"
#include "../../shaders/texture.h"
#include "./mesh.h"
#include "./renderable3d.h"

namespace neon {

	class Model : Renderable3d {
	public:
		Model(const char *filename, Program* program);
		~Model();

		// GETTERS
		inline const Mesh* GetMesh() const { return m_mesh; }
		inline const glm::mat4& GetModelMatrix() const { return m_modelMatrix; }

		// SETTERS
		inline void SetModelMatrix(const glm::mat4 &n_modelMatrix) { m_modelMatrix = n_modelMatrix; }
		inline void SetColor(const glm::vec4 &n_color) { m_color = n_color; }
		void SetTexture(const char* filename);

		// Draw Functions
		void Draw() const;

	private:
		void Init();
		void BuildVertexData();

	private:
		GLuint m_vao;
		GLuint m_vbo;

		IndexBuffer *m_ibo;
		Program *m_program;

		/* 
			TODO: Maybe I shouldn't declare this on the heap...?
		*/
		Mesh *m_mesh;
		Texture *m_texture;

		glm::mat4 m_modelMatrix;
		GLuint m_modelLoc;
		GLuint m_colorLoc;
		
		glm::vec4 m_color;
	};
}