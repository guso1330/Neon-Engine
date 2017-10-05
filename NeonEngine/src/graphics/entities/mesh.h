#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "../../utils/obj_loader/objloader.h"

namespace neon {
	class Mesh {
		public:
			/***************
			* CONSTRUCTORs *
			***************/
			Mesh(); // default constructor
			Mesh(const char *filename); // Parametric constructor

			/* Manipulator Functions */
			void InitMesh(const char *filename);

			/********************
			*  Getter functions *
			********************/
			inline std::vector<glm::vec3>& GetVertices() { return m_vertices; }
			inline unsigned int GetVerticesSize() const { return m_vertices.size(); }

			inline std::vector<unsigned int>& GetIndices() { return m_indices; }
			inline unsigned int GetIndicesSize() const { return m_indices.size(); }
			
			inline std::vector<glm::vec2>& GetUVs() { return m_uvs; }
			inline unsigned int GetUVsSize() const { return m_uvs.size(); }
			
			inline std::vector<glm::vec3>& GetNormals() { return m_normals; }
			inline unsigned int GetNormalsSize() const { return m_normals.size(); }

			// Virtual Functions
			// virtual void DrawSolid() = 0;
			// virtual void DrawWireframe() = 0;

		private:
			std::vector<glm::vec3> m_vertices;
			std::vector<unsigned int> m_indices;
			std::vector<glm::vec2> m_uvs;
			std::vector<glm::vec3> m_normals;
	};
}