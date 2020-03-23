#include "BaseECS/CameraSystem.h"

namespace Neon { namespace ECS {
	bool CameraSystem::Init() {
		return true;
	}

	void CameraSystem::Update(Timestep ts) {
		CameraComponent* camera_component;
		TransformComponent* transform_component;
		EntityMap entities;

		entities = ECSManager::GetInstance().GetEntities();

		for (EntityMap::const_iterator it = entities.begin(); it != entities.end(); ++it) {
			camera_component = ECSManager::GetInstance().GetComponent<CameraComponent>((*it).first);
			transform_component = ECSManager::GetInstance().GetComponent<TransformComponent>((*it).first);

			if (camera_component != nullptr && transform_component != nullptr) {
				camera_component->cameraData->camera.SetPosition(
					transform_component->transformData->transform.GetPosition()
				);
				camera_component->cameraData->camera.Update();
			}
		}
	}
}}
