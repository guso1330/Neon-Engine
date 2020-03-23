#pragma once

#include "Graphics/Entities/transform.h"
#include "Core/ECS/IComponent.h"

namespace Neon { namespace ECS {
	struct TransformData {
		Neon::Transform transform;
	};

	struct TransformComponent : public Neon::ECS::IComponent {
		virtual bool Init(void* n_data) override;

		TransformData* transformData;
	};
}}
