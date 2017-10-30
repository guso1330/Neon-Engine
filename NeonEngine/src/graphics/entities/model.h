#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "../buffers/vertexArray.h"
#include "../buffers/vertexBuffer.h"
#include "../buffers/indexBuffer.h"
#include "./mesh.h"
#include "../../shaders/program.h"
#include "../../shaders/texture.h"

#include <unordered_set>
#include <set>
#include <tuple>
#include <utility>
#include <iterator>

namespace neon {

	struct Vertex {
		glm::vec3 pos;
		glm::vec2 uv;
		glm::vec3 normal;

		bool vecLessThan(const glm::vec3& lhs, const glm::vec3& rhs) const {
			return glm::all(glm::lessThan(lhs, rhs));
		}
		bool vecLessThan(const glm::vec2& lhs, const glm::vec2& rhs) const {
			return glm::all(glm::lessThan(lhs, rhs));
		}

		bool operator == (const Vertex& rhs) const
		{
			return (glm::all(glm::equal(pos, rhs.pos)) && 
					glm::all(glm::equal(uv, rhs.uv))   && 
					glm::all(glm::equal(normal, rhs.normal))); 
		}

		bool operator < (const Vertex& rhs) const
		{
			// return vecLessThan(pos, rhs.pos) ||
			// 	   (!vecLessThan(pos, rhs.pos) && vecLessThan(uv, rhs.uv)) ||
			// 	   (!(vecLessThan(uv, rhs.uv)) && vecLessThan(normal, rhs.normal));
			// std::cout << ((std::tie(pos.x, pos.y, pos.z) < std::tie(rhs.pos.x, rhs.pos.y, rhs.pos.z)) ||
			// 				   (!(std::tie(pos.x, pos.y, pos.z) < std::tie(rhs.pos.x, rhs.pos.y, rhs.pos.z)) && std::tie(uv.x, uv.y) < std::tie(rhs.uv.x, rhs.uv.y)) ||
			// 				   (!(std::tie(uv.x, uv.y) < std::tie(rhs.uv.x, rhs.uv.y)) && std::tie(normal.x, normal.y, normal.z) < std::tie(rhs.normal.x, rhs.normal.y, rhs.normal.z))) << std::endl;

			return (std::tie(pos.x, pos.y, pos.z) < std::tie(rhs.pos.x, rhs.pos.y, rhs.pos.z)) ||
				   (!(std::tie(pos.x, pos.y, pos.z) < std::tie(rhs.pos.x, rhs.pos.y, rhs.pos.z)) && std::tie(uv.x, uv.y) < std::tie(rhs.uv.x, rhs.uv.y)) ||
				   (!(std::tie(uv.x, uv.y) < std::tie(rhs.uv.x, rhs.uv.y)) && std::tie(normal.x, normal.y, normal.z) < std::tie(rhs.normal.x, rhs.normal.y, rhs.normal.z));

			// return a.field1 < b.field1 || (
			// 	!(b.field1 < a.field1) && a.field2 < b.field2
			// );
			// return (glm::all(glm::lessThan(pos, rhs.pos)) || (pos == rhs.pos && (glm::all(glm::lessThan(uv, rhs.uv))|| (uv == rhs.uv && glm::all(glm::lessThan(normal, rhs.normal))))));

		}
	};


	class Model {
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

		// VertexArray m_vao;
		IndexBuffer *m_ibo;
		Program *m_program;

		std::vector<Vertex> m_vertexData;
		std::vector<unsigned int> m_indices;

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