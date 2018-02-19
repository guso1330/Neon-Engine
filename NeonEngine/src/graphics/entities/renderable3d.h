/*******************************************************************
*	Class: Renderable
*
*	Description: This is a 3d renderable class that implements
*				 virtual classes for rendering various 3d classes
*				 such as primitives, models, and other 3d meshes 
*******************************************************************/

#pragma once

#include "../buffers/vertexArray.h"
#include "../buffers/vertexBuffer.h"
#include "../buffers/indexBuffer.h"
#include "../../shaders/program.h"
#include "../../shaders/texture.h"
#include "./transform.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <set>
#include <ctime>

namespace neon {

	struct Vertex {
		glm::vec3 pos;
		glm::vec2 uv;
		glm::vec3 normal;

		/* Operator functions */
		bool operator == (const Vertex& rhs) const
		{
			return (glm::all(glm::equal(pos, rhs.pos)) && 
					glm::all(glm::equal(uv, rhs.uv))   && 
					glm::all(glm::equal(normal, rhs.normal))); 
		}
		bool operator < (const Vertex& rhs) const
		{
			return (std::tie(pos.x, pos.y, pos.z) < std::tie(rhs.pos.x, rhs.pos.y, rhs.pos.z)) ||
				   (!(std::tie(pos.x, pos.y, pos.z) < std::tie(rhs.pos.x, rhs.pos.y, rhs.pos.z)) && std::tie(uv.x, uv.y) < std::tie(rhs.uv.x, rhs.uv.y)) ||
				   (!(std::tie(uv.x, uv.y) < std::tie(rhs.uv.x, rhs.uv.y)) && std::tie(normal.x, normal.y, normal.z) < std::tie(rhs.normal.x, rhs.normal.y, rhs.normal.z));
		}
	};

	class Renderable3d {

		public:
			Renderable3d(Program* program);

			void Draw() const;
			void Draw(glm::mat4 tranform) const;

			// Getters
			inline const std::vector<Vertex> 		&GetVertexData() const { return m_vertexData; }
			inline const std::vector<unsigned int>  &GetIndexData() const { return m_indices; }
			inline Transform 						&GetTransform() { return m_transform; }
			inline const GLuint						&GetVao() const { return m_vao; }
			
			// SETTERS
			inline void SetColor(const glm::vec4 &n_color) { m_color = n_color; }
			void 		SetTexture(const char* filename); // Generate a new texture
			void 		SetTexture(Texture& n_texture); // Pass in a texture that already exists
			void 		SetUpDraw(const glm::mat4 &transform) const;
			void 		UnSetDraw() const;

		protected:
			virtual ~Renderable3d() {}
			void 	SendVertexData();

		protected:
			// GL id's for self drawing
			GLuint 		m_vao, m_vbo;
			IndexBuffer *m_ibo;
			GLuint 		m_modelLoc;
			GLuint 		m_colorLoc;
			glm::vec4 	m_color;

			Program   *m_program;
			Texture   *m_texture;
			Transform m_transform;

			std::vector<Vertex> 	  m_vertexData;
			std::vector<unsigned int> m_indices;

		protected: 
			// Flags
			bool isDataSent;
	};
}