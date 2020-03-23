#pragma once

#include "Graphics/Cameras/Camera.h"
#include "Core/ECS/IComponent.h"

namespace Neon { namespace ECS {
	struct CameraData {
		Neon::Camera camera;
	};

	struct CameraComponent : public Neon::ECS::IComponent {
		virtual bool Init(void* n_data) override;

		CameraData* cameraData;
	};
}}
