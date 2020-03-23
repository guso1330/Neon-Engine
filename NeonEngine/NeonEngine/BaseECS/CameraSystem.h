#pragma once

#include "Core/ECS/ISystem.h"
#include "Core/ECS/ECSManager.h"
#include "BaseECS/TransformComponent.h"
#include "BaseECS/CameraComponent.h"

namespace Neon { namespace ECS {
	class CameraSystem : public Neon::ECS::ISystem {
		public:
			virtual bool Init() override;

			virtual void Update(Neon::Timestep ts) override;
	};
}}
