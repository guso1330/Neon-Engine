#include "BaseECS/TransformComponent.h"

namespace Neon { namespace ECS {
	bool TransformComponent::Init(void* n_data) {
		transformData = static_cast<TransformData*>(n_data);
		return true;
	}
}}
