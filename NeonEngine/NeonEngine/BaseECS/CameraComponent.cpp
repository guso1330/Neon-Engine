#include "BaseECS/CameraComponent.h"

namespace Neon { namespace ECS {
	bool CameraComponent::Init(void* n_data) {
		cameraData = static_cast<CameraData*>(n_data);

		return true;
	}
}}
