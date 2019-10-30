/*******************************************************************
*	Class: Renderable
*
*	Description: This is a 3d renderable class that implements
*				 virtual classes for rendering various 3d classes
*				 such as primitives, models, and other 3d meshes 
*******************************************************************/

#pragma once

#include "Graphics/Entities/vertex.h"
#include "Core/Platforms/OpenGL/VertexBuffer.h"
#include "Core/Platforms/OpenGL/IndexBuffer.h"
#include "Core/Platforms/OpenGL/VertexArray.h"
#include "Core/Platforms/OpenGL/program.h"
#include "Shaders/material.h"
#include "Graphics/Entities/transform.h"

#include <vector>
#include <iostream>

namespace Neon {

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