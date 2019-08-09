#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../core/platform/opengl/texture.h"
#include "./mesh.h"
#include "./renderable3d.h"

namespace neon {

	class Model {
	public:
		Model(const char* filename);
		~Model();

		// GETTERS
		inline const std::vector<Mesh*> &GetMeshes() const { return m_meshes; }

	private:
		void Init(const char* filename);

		// Assimp Model Loading functions
		bool InitMeshes(const char* filename);
		void AssimpProcessNode(aiNode *node, const aiScene *scene);
		Mesh* AssimpProcessMesh(aiMesh *mesh, const aiScene *scene);

	private:
		std::vector<Mesh*> m_meshes;
		std::string m_directory;
	};
}