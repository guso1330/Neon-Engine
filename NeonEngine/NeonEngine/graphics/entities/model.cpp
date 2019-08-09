#include "model.h"


namespace neon {
	Model::Model(const char* filename) {
		Init(filename);
	}

	Model::~Model() {}

	void Model::Init(const char* filename) {
		bool loaded_mesh = InitMeshes(filename);
		if(!loaded_mesh) {
			std::cout << "Error: " << filename << " was not loaded" << std::endl;
		} else {
			std::string mesh_word = m_meshes.size() > 1 ? "meshes" : "mesh";
			std::cout << "Mesh: " << filename << " loaded succesfully with " << m_meshes.size() << " " << mesh_word << " loaded" << std::endl;
		}
	}

	bool Model::InitMeshes(const char* filename) {
		Assimp::Importer importer;
		std::string filename_string = (std::string)filename;

		std::cout << "\nAssimp Loading: " << filename_string << std::endl;

		// Load the scene
		const aiScene* scene = importer.ReadFile(filename_string, aiProcessPreset_TargetRealtime_MaxQuality);

		// Check if there was errors with 
		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << importer.GetErrorString() << std::endl;
			return false;
		}

		m_directory = filename_string.substr(0, filename_string.find_last_of('/'));

		AssimpProcessNode(scene->mRootNode, scene);

		return true;
	}

	void Model::AssimpProcessNode(aiNode *node, const aiScene *scene) {
		for(unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			m_meshes.push_back(AssimpProcessMesh(mesh, scene));
		}
		for(unsigned int i = 0; i < node->mNumChildren; i++)
		{
			AssimpProcessNode(node->mChildren[i], scene);
		}
	}

	Mesh* Model::AssimpProcessMesh(aiMesh *mesh, const aiScene *scene) {
		Material *n_material = new Material();
		std::vector<Vertex> vertex_data;
		std::vector<unsigned int> indices;

		for(unsigned int i = 0; i < mesh->mNumVertices; ++i)
		{
			Vertex vertex;
			// process vertex positions, normals and texture coordinates
			vertex.pos.x = mesh->mVertices[i].x;
			vertex.pos.y = mesh->mVertices[i].y;
			vertex.pos.z = mesh->mVertices[i].z;

			// UVs coordinates
			if(mesh->mTextureCoords[0]) // domes the mesh contain texture coordinates?
			{
				vertex.uv.x = mesh->mTextureCoords[0][i].x; 
				vertex.uv.y = mesh->mTextureCoords[0][i].y;
			}
			else {
				vertex.uv.x = 0.0f;
				vertex.uv.y = 0.0f;
			}

			// Normals
			vertex.normal.x = mesh->mNormals[i].x;
			vertex.normal.y = mesh->mNormals[i].y;
			vertex.normal.z = mesh->mNormals[i].z;

			//
			// TODO: Handle tangent and bittangent
			//
			vertex_data.push_back(vertex);
		}

		// process indices
		for(unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for(unsigned int j = 0; j < face.mNumIndices; j++) {
				indices.push_back(face.mIndices[j]);
			}
		}

		// process material
		if(mesh->mMaterialIndex >= 0)
		{
			// Handle materials
			aiMaterial *ai_material = scene->mMaterials[mesh->mMaterialIndex];

			aiString filename;
			if(aiReturn_SUCCESS == ai_material->GetTexture(aiTextureType_DIFFUSE, 0, &filename))
			{
				std::string diffuse_path = m_directory + "/" + std::string(filename.C_Str());
				std::cout << "Diffuse Texture Path: " << diffuse_path << std::endl;
				n_material->SetDiffuse(new Texture(diffuse_path, Diffuse));
			} else if (aiReturn_SUCCESS == ai_material->GetTexture(aiTextureType_SPECULAR, 0, &filename)) {
				std::cout << "Specular Texture Path: " << filename.C_Str() << std::endl;
				std::string diffuse_path = m_directory + "/" + std::string(filename.C_Str());
				n_material->SetSpecular(new Texture(diffuse_path, Specular));
			}
		}

		Mesh *n_mesh = new Mesh(vertex_data, indices, n_material);

		return n_mesh;
	}
}