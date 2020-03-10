#pragma once

#include "Core/ECS/ECSTypes.h"

namespace Neon { namespace ECS {
	class IComponent {
		public:
			/* Constructor/Destructor */
			virtual ~IComponent() = default;

			/* Methods */
			virtual bool Init(void* data) = 0;
		private:
			ComponentID id;
	};
}}
