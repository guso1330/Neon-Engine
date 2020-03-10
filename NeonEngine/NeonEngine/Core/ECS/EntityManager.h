#pragma once

#include "Core/ECS/ECSTypes.h"
#include "Core/ECS/Entity.h"
#include "Core/ECS/ISystem.h"
#include "Core/Time/Timer.h"
#include "nepch.h"

namespace Neon { namespace ECS {
	class EntityManager {
		public:
			/* Constructor/Destructor */
			EntityManager() = default;
			~EntityManager() = default;

			/* Methods */
			bool Init();
			void Update(Timestep ts);

		private:
			std::vector<ISystem*> m_systems;
			std::unordered_map<EntityID, Entity*> m_entities;
	};
}}
