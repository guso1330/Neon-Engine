#pragma once

#include "App/Timer.h"
#include "Core/ECS/ECSTypes.h"

namespace Neon { namespace ECS {
	class ISystem {
		public:
			virtual ~ISystem() = default;

			/* Methods */
			virtual bool Init() = 0;
			virtual void Update(Timestep ts) = 0;
	};
}}
