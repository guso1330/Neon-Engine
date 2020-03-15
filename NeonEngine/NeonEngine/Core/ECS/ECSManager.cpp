#include "Core/ECS/ECSManager.h"

namespace Neon { namespace ECS {
	bool ECSManager::Init(size_t entityPoolSize, size_t systemPoolSize) {
		if (
			ECSMemory::EntityPool.Init<Entity>(entityPoolSize, alignof(Entity)) &&
			ECSMemory::SystemPool.Init<ISystem>(systemPoolSize, alignof(ISystem))
		) {
			return true;
		}

		return false;
	}

	void ECSManager::Update(Timestep ts) {
		for (SystemMap::iterator it = m_systemsMap.begin(); it != m_systemsMap.end(); ++it) {
			it->second->Update(ts);
		}
	}

	ECSManager& ECSManager::GetInstance() {
		static ECSManager instance;
		return instance;
	}

	/* Entity Methods */
	EntityID ECSManager::CreateEntity() {
		Entity* n_entity;
		EntityID n_id;

		n_id = m_entityID;
		// TODO: Pass in allocators here instead of inside Entity.cpp
		n_entity = new Entity(n_id);
		m_entityMap.insert(std::make_pair(n_id, n_entity));
		++m_entityID;

		return n_id;
	}

	Entity* ECSManager::GetEntity(EntityID id) const {
		EntityMap::const_iterator it;
		Entity* n_entity;

		it = m_entityMap.find(id);
		if (it != m_entityMap.end()) {
			n_entity = it->second;
		}

		return n_entity;
	}

	void ECSManager::DestroyEntity(EntityID id) {
		EntityMap::const_iterator it;
		Entity* n_entity;

		it = m_entityMap.find(id);
		if (it != m_entityMap.end()) {
			n_entity = it->second;
			delete n_entity;
			m_entityMap.erase(it);
		}
	}

	// /* System Methods */
	// void ECSManager::AddSystem(ISystem* system) {

	// }
}}
