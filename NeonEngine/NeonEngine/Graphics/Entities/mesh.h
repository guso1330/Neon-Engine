#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Graphics/Entities/vertex.h"
#include "Shaders/material.h"

namespace Neon {
	class Mesh {
		public:
			/***************
			* CONSTRUCTORs *
			***************/
			Mesh(); // default constructor
			Mesh(std::vector<Vertex> &vertex_data, std::vector<unsigned int> &indices); // Parametric constructor
			Mesh(std::vector<Vertex> &vertex_data, std::vector<unsigned int> &indices, Material* n_material); // Parametric constructor

			/********************
			*  Getter functions *
			********************/
			inline const std::vector<glm::vec3>& GetVertices() const { return m_vertices; }
			inline const unsigned int GetVerticesSize() const { return m_vertices.size(); }

			inline const std::vector<unsigned int>& GetIndices() const { return m_indices; }
			inline const unsigned int GetIndicesSize() const { return m_indices.size(); }
			
			inline const std::vector<glm::vec2>& GetUVs() const { return m_uvs; }
			inline const unsigned int GetUVsSize() const { return m_uvs.size(); }
			
			inline const std::vector<glm::vec3>& GetNormals() const { return m_normals; }
			inline const unsigned int GetNormalsSize() const { return m_normals.size(); }

			inline const std::vector<Vertex>& GetVertexData() const { return m_vertexData; }
			inline const unsigned int GetVertexDataSize() const { return m_vertexData.size(); }
			
			inline const Material* GetMaterial() const { return m_material; }

			/********************
			*  Setter functions *
			********************/
			inline void SetMaterial(Material *n_material) { m_material = n_material; }

		private:
			std::vector<glm::vec3> m_vertices;
			std::vector<unsigned int> m_indices;
			std::vector<glm::vec2> m_uvs;
			std::vector<glm::vec3> m_normals;
			std::vector<Vertex> m_vertexData;

			Material* m_material;
	};
}