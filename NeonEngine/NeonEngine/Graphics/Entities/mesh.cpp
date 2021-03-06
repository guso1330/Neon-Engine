// Implementation file for the Mesh Class
#include "./mesh.h"

namespace Neon {
	// Default
	Mesh::Mesh() {}

	// Parametric Constructor
	Mesh::Mesh(std::vector<Vertex> &vertex_data, std::vector<unsigned int> &indices) :
		m_vertexData(vertex_data),
		m_indices(indices),
		m_material(nullptr)
	{
		for(std::vector<Vertex>::iterator it = vertex_data.begin(); it != vertex_data.end(); ++it) {
			m_vertices.push_back((*it).pos);
			m_uvs.push_back((*it).uv);
			m_normals.push_back((*it).normal);
		}
	}

	Mesh::Mesh(std::vector<Vertex> &vertex_data, std::vector<unsigned int> &indices, Material* n_material) :
		m_vertexData(vertex_data),
		m_indices(indices),
		m_material(n_material)
	{
		for(std::vector<Vertex>::iterator it = vertex_data.begin(); it != vertex_data.end(); ++it) {
			m_vertices.push_back((*it).pos);
			m_uvs.push_back((*it).uv);
			m_normals.push_back((*it).normal);
		}
	}
}
