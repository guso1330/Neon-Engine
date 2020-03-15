#pragma once

#include "Core/Types/Singleton.h"
#include "Core/Time/Timer.h"
#include "Core/ECS/ECSTypes.h"
#include "Core/ECS/ECSMemory.h"
#include "Core/ECS/Entity.h"
#include "Core/ECS/IComponent.h"
#include "Core/ECS/ISystem.h"
#include "Core/Core.h"

namespace Neon { namespace ECS {
	class ECSManager : public Singleton {
		public:
			/* Constructor/Destructor */
			~ECSManager() = default;

			/* Methods */
			bool Init(size_t entityPoolSize = NE_DEFAULT_ENTITY_POOL_SIZE, size_t systemPoolSize = NE_DEFAULT_SYSTEM_POOL_SIZE);
			void Update(Timestep ts);

			/* Getters */
			static ECSManager& GetInstance();
			inline const EntityMap& GetEntities() const { return m_entityMap; }

			/* Entity Methods */
			EntityID CreateEntity();
			Entity* GetEntity(EntityID id) const;
			void DestroyEntity(EntityID id);

			/* Component Methods */
			template<class T>
			T* CreateComponent(EntityID entityID, void* data, size_t componentPoolSize = NE_DEFAULT_COMPONENT_POOL_SIZE);
			template<class T>
			T* GetComponent(EntityID entityID) const;
			// TODO: DestroyComponent()

			/* System Methods */
			template<class T>
			T* CreateSystem();
			template<class T>
			T* GetSystem() const;
			// TODO: DestroySystem()

		private:
			EntityID m_entityID;
			SystemMap m_systemsMap;
			EntityMap m_entityMap;
	};
}}

#include "Core/ECS/ECSManager.tpp"
