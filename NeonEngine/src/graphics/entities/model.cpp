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
			std::string mesh_word = m_meshes.size() > 1 ? "meshes" : "mesh";
			std::cout << filename << " loaded succesfully with " << m_meshes.size() << " " << mesh_word << " loaded" << std::endl;
			std::cout << "Materials loaded: " << m_materials.size() << std::endl;
		}

		isDataSent = shouldSendData;
		if(shouldSendData) {
			SendVertexData();
		}

		for(int i=0; i < m_meshes.size(); ++i) {
			std::cout << "IBO size:" << m_ibo->GetCount() << std::endl;
			std::cout << "Mesh index: " << m_meshes[i]->GetIndex() << std::endl;
			std::cout << "Mesh indices size:" << m_meshes[i]->GetIndicesSize() << std::endl;
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
		Material *n_material = new Material();
		unsigned int mesh_index = m_vertexData.size();

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
			aiMaterial *ai_material = scene->mMaterials[mesh->mMaterialIndex];

			aiString filename;
			if(aiReturn_SUCCESS == ai_material->GetTexture(aiTextureType_DIFFUSE, 0, &filename))
			{
				std::string diffuse_path = m_directory + "/" + std::string(filename.C_Str());
				std::cout << "Diffuse Texture Path: " << diffuse_path << std::endl;
				n_material->diffuse = new Texture(diffuse_path, Diffuse);
			} else if (aiReturn_SUCCESS == ai_material->GetTexture(aiTextureType_SPECULAR, 0, &filename)) {
				std::cout << "Specular Texture Path: " << filename.C_Str() << std::endl;
				std::string diffuse_path = m_directory + "/" + std::string(filename.C_Str());
				n_material->specular = new Texture(diffuse_path, Specular);
			}

			// Todo: Probably can remove the m_materials vector, because I don't need to store the materials
			m_materials.push_back(n_material);
		}

		Mesh *n_mesh = new Mesh(m_vertexData, m_indices, n_material);
		n_mesh->SetIndex(mesh_index);

		return n_mesh;
	}

	void Model::DrawInit() const {
		m_program->Bind();
		m_vao->Bind();
		m_ibo->Bind();
	}

	void Model::SetUpDraw(const glm::mat4 &transform, Mesh *mesh) const {
		if(mesh->GetMaterial()->diffuse != nullptr) {
			mesh->GetMaterial()->Bind(m_program);
		} else {
			m_material->Bind(m_program);
		}

		m_program->SetUniform4f(m_colorLoc, m_color);
		m_program->SetUniformMat4(m_modelLoc, transform);
		// Handle material switching
		GL_Call(glDrawElementsBaseVertex(GL_TRIANGLES, mesh->GetIndicesSize(), GL_UNSIGNED_INT, NULL, mesh->GetIndex()));
	}

	void Model::UnSetDraw(Mesh *mesh) const {
		if(mesh->GetMaterial()->diffuse != nullptr) {
			mesh->GetMaterial()->Unbind();
		} else {
			m_material->Unbind();
		}
	}

	// TODO: Better way of determining if a material is set or not.
	//		 Adjust to make sure that the code duplication between
	//		 these two versions of the model::draw functions and the
	//		 Renderable3d::draw versions from aren't overlapping.
	void Model::Draw() const {
		this->DrawInit();

		for(int i=0; i < m_meshes.size(); ++i) {
			this->SetUpDraw(m_transform.GetModelMatrix(), m_meshes[i]);
			this->UnSetDraw(m_meshes[i]);
		}
	}

	void Model::Draw(const glm::mat4 &transform) const {
		this->DrawInit();

		for(int i=0; i < m_meshes.size(); ++i) {
			this->SetUpDraw(transform, m_meshes[i]);
			this->UnSetDraw(m_meshes[i]);
		}
	}
}