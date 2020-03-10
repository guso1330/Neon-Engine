#pragma once

#include "Core/ECS/ECSTypes.h"

namespace Neon { namespace ECS {
	class IComponent {
		public:
			virtual ~IComponent() = default;
			virtual bool Init(void* data) = 0;
		private:
			ComponentID id;
	};
}}
