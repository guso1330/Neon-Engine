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

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <unordered_set>
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

			// Getters
			const std::vector<Vertex> &GetVertexData() const { return m_vertexData; }
			const glm::mat4 &GetModelMatrix() const { return m_modelMatrix; }
			const glm::vec3 &GetPosition() const { return m_position; }
			
			// SETTERS
			inline void SetModelMatrix(const glm::mat4 &n_modelMatrix) { m_modelMatrix = n_modelMatrix; }
			inline void SetColor(const glm::vec4 &n_color) { m_color = n_color; }
			void SetPosition(const glm::vec3 &n_pos);
			void SetTexture(const char* filename);
			void SetTexture(Texture& n_texture);

		protected:
			virtual ~Renderable3d() {}
			virtual void BuildVertexData() = 0;
			void SendVertexData();

		protected:
			GLuint m_vao, m_vbo;
			IndexBuffer *m_ibo;

			Program *m_program;
			Texture *m_texture;

			glm::vec3 m_position;
			glm::mat4 m_modelMatrix;
			GLuint m_modelLoc;
			GLuint m_colorLoc;
			glm::vec4 m_color;

			std::vector<Vertex> m_vertexData;
			std::vector<unsigned int> m_indices;
	};
}