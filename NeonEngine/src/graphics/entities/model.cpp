#include "model.h"


namespace neon {
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);

	Model::Model(const char *filename, Program* program, bool shouldSendData) : 
		Renderable3d(program)
	{
		bool loaded_mesh = InitMeshes(filename);
		if(!loaded_mesh) {
			std::cout << "Error: " << filename << " was not loaded" << std::endl;
		} else {
			std::cout << filename << " loaded succesfully with " << m_meshes.size() << " meshes loaded" << std::endl;
			std::cout << "Materials loaded: " << m_materials.size() << std::endl;
		}

		isDataSent = shouldSendData;
		if(shouldSendData) {
			SendVertexData();
		}
	}

	Model::~Model() {}

	bool Model::InitMeshes(const std::string &filename) {
		Assimp::Importer importer;

		std::cout << "\nAssimp Loading: " << filename << std::endl;

		// Load the scene
		const aiScene* scene = importer.ReadFile( 
			filename,
			aiProcessPreset_TargetRealtime_Quality);

		// Check if there was errors with 
		if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << importer.GetErrorString() << std::endl;
			return false;
		}

		m_directory = filename.substr(0, filename.find_last_of('/'));

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
		std::vector<Texture> textures;
		
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
			m_vertexData.push_back(vertex);
		}

		// process indices
		for(unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];

			for(unsigned int j = 0; j < face.mNumIndices; j++) {
				m_indices.push_back(face.mIndices[j]);
			}
		}

		// process material
		if(mesh->mMaterialIndex >= 0)
		{
			// Handle materials
			aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

			aiString path;
			if(aiReturn_SUCCESS == material->GetTexture(aiTextureType_DIFFUSE, 0, &path))
			{
				std::cout << "Path Name: " << path.C_Str() << std::endl;
				std::cout << "Directory: " << m_directory << std::endl;
			}
			// Todo: Probably can remove the m_materials vector, because I don't need to store the materials
			m_materials.push_back(material);
		}

		Mesh *n_mesh = new Mesh(m_vertexData, m_indices);

		return n_mesh;
	}
}