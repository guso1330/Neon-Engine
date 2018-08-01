#pragma once

#include "../graphics/cameras/camera.h"
#include "../shaders/material.h"
#include "../graphics/entities/mesh.h"
#include "../graphics/entities/transform.h"
#include "../graphics/cameras/camera.h"
#include "../utils/file_utils/fileUtils.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <string>
#include <vector>
#include <map>
#include <string>

namespace neon {
	class Scene {
		public:
			Scene();
			~Scene();

			void LoadSettings(const char *filename);

		private:
			std::vector<Camera*> m_cameras;
			std::string settings;
	};
}

// struct DiffuseMap
// {
//     GLuint DiffuseMapTO;
// };

// struct Instance
// {
//     uint32_t MeshID;
//     uint32_t TransformID;
// };

// class Scene
// {
// public:
//     packed_freelist<DiffuseMap> DiffuseMaps;
//     packed_freelist<Material> Materials;
//     packed_freelist<Mesh> Meshes;
//     packed_freelist<Transform> Transforms;
//     packed_freelist<Instance> Instances;
//     packed_freelist<Camera> Cameras;

//     uint32_t MainCameraID;

//     void Init();
// };

// void LoadMeshes(
//     Scene& scene,
//     const std::string& filename,
//     std::vector<uint32_t>* loadedMeshIDs);

// void AddInstance(
//     Scene& scene,
//     uint32_t meshID,
//     uint32_t* newInstanceID);