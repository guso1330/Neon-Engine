/*******************************************************************
*	Class: Renderable
*
*	Description: This is a 3d renderable class that implements
*				 virtual classes for rendering various 3d classes
*				 such as primitives, models, and other 3d meshes 
*******************************************************************/

#pragma once

#include "./vertex.h"
#include "../buffers/vertexArray.h"
#include "../buffers/vertexBuffer.h"
#include "../buffers/indexBuffer.h"
#include "../../shaders/program.h"
#include "../../shaders/texture.h"
#include "./transform.h"

#include <vector>
#include <iostream>

namespace neon {

	class Renderable3d {

		public:
			Renderable3d(Program* program);

			void Draw() const;
			void Draw(const glm::mat4 &tranform) const;

			// Getters
			inline const std::vector<Vertex> 		&GetVertexData() const { return m_vertexData; }
			inline const std::vector<unsigned int>  &GetIndexData() const { return m_indices; }
			inline Transform 						&GetTransform() { return m_transform; }
			inline VertexArray*						&GetVao() { return m_vao; }
			inline const unsigned int 				GetIbo() const { return m_ibo->GetIbo(); }
			
			// SETTERS
			inline void SetColor(const glm::vec4 &n_color) { m_color = n_color; }
			void 		SetTexture(const char* filename); // Generate a new texture
			void 		SetTexture(Texture& n_texture); // Pass in a texture that already exists
			void 		SetSpecularTexture(const char* filename); // Generate a new texture
			void 		SetSpecularTexture(Texture& n_texture); // Pass in a texture that already exists
			void 		SetUpDraw(const glm::mat4 &transform) const;
			void 		UnSetDraw() const;

		protected:
			virtual ~Renderable3d();
			void 	SendVertexData();
			// NOTE: you must build m_indices and m_vertexData,
			// because they're used in SendVertexData()
			virtual void BuildVertexData() = 0;
		protected:
			// GL id's for self drawing
			// GLuint 		m_vao, m_vbo;
			VertexBuffer *m_vbo;
			IndexBuffer *m_ibo;
			VertexArray *m_vao;

			GLuint 		m_modelLoc;
			GLuint 		m_colorLoc;
			glm::vec4 	m_color;

			Program   *m_program;
			Texture   *m_texture;
			Texture   *m_specular_texture;	
			Transform m_transform;

			std::vector<Vertex> 	  m_vertexData;
			std::vector<unsigned int> m_indices;

		protected: 
			// Flags
			bool isDataSent;
	};
}