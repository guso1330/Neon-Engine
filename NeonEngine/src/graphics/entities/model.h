#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../../shaders/texture.h"
#include "./mesh.h"
#include "./renderable3d.h"

namespace neon {

	class Model : public Renderable3d {
	public:
		Model(const char *filename, bool shouldSendData = true);
		Model(const char *filename, Program* program, bool shouldSendData = true);
		~Model();

		// GETTERS
		inline const std::vector<Mesh*> &GetMeshes() const { return m_meshes; }

		void Init(const char *filename, bool shouldSendData);

		// Assimp Model Loading functions
		bool InitMeshes(const std::string &filename);

		void DrawInit() const;
		void SetUpDraw(const glm::mat4 &transform, Mesh* mesh) const;
		void UnSetDraw(Mesh* mesh) const;

		void Draw() const;
		void Draw(const glm::mat4 &transform) const;

	private:
		void AssimpProcessNode(aiNode *node, const aiScene *scene);
		Mesh* AssimpProcessMesh(aiMesh *mesh, const aiScene *scene);

	private:
		std::vector<Mesh*> m_meshes;
		std::string m_directory;
		std::vector<Material*> m_materials;
	};
}