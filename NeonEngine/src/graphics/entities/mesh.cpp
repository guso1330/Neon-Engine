// Implementation file for the Mesh Class
#include "./mesh.h"

namespace neon {
	// Default
	Mesh::Mesh() {}

	// Parametric Constructor
	Mesh::Mesh(const char *filename) {
		InitMesh(filename);
	}

	void Mesh::InitMesh(const char *filename) {
		tiny_obj_loader_load_obj(filename, m_vertices, m_indices, m_uvs, m_normals, m_indexObj);
	}
}
