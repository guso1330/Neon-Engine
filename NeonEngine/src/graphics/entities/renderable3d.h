/*******************************************************************
*	Class: Renderable
*
*	Description: This is a 3d renderable class that implements
*				 virtual classes for rendering various 3d classes
*				 such as primitives, models, and other 3d meshes 
*******************************************************************/

#pragma once

#include "./vertex.h"
#include "../../core/platform/opengl/vertexArray.h"
#include "../../core/platform/opengl/vertexBuffer.h"
#include "../../core/platform/opengl/indexBuffer.h"
#include "../../core/platform/opengl/program.h"
#include "../../shaders/material.h"
#include "./transform.h"

#include <vector>
#include <iostream>

namespace neon {

	class Renderable3d {

		public:
			Renderable3d();
			Renderable3d(Program* program);

			virtual void Draw() const;
			virtual void Draw(const glm::mat4 &transform) const;

			// Getters
			inline const std::vector<Vertex> &GetVertexData() const { return m_vertexData; }
			inline const std::vector<unsigned int> &GetIndexData() const { return m_indices; }
			inline Transform &GetTransform() { return m_transform; }
			inline VertexArray* &GetVao() { return m_vao; }
			inline IndexBuffer* &GetIbo() { return m_ibo; }
			inline const glm::vec4 &GetColor() const { return m_color; }
			inline const Material* GetMaterial() const { return m_material; }
			
			// SETTERS
			inline void SetColor(const glm::vec4 &n_color) { m_color = n_color; }
			void SetTexture(const std::string &filename, TextureType type = Diffuse); // Generate a new texture
			void SetTexture(Texture* n_texture, TextureType type); // Pass in a texture that already exists

			virtual void SetUpDraw(const glm::mat4 &transform) const;
			virtual void UnSetDraw() const;

		protected:
			virtual ~Renderable3d();
			void SendVertexData();

			// NOTE: you must build m_indices and m_vertexData,
			// because they're used in SendVertexData()
			// virtual void BuildVertexData() = 0;
		protected:
			VertexBuffer *m_vbo;
			IndexBuffer *m_ibo;
			VertexArray *m_vao;

			GLuint m_modelLoc;
			GLuint m_normalMatrixLoc;
			GLuint m_colorLoc;
			glm::vec4 m_color;

			Program *m_program;
			Transform m_transform;

			Material *m_material;
			std::vector<Vertex> m_vertexData;
			std::vector<unsigned int> m_indices;

		protected: 
			// Flags
			bool isDataSent;
	};
}