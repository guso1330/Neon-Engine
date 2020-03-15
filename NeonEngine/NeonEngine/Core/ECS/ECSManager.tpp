namespace Neon { namespace ECS {
	template<class T>
	T* ECSManager::CreateComponent(EntityID entityID, void* data, size_t componentPoolSize) {
		T* n_component;
		Entity* n_entity;
		Memory::PoolAllocator* n_PAllocator;
		ComponentType type;
		ComponentPoolMap::iterator it;

		// Check if ComponentPools type is defined
		type = typeid(T).hash_code();
		it = ECSMemory::ComponentPools.find(type);
		if (it == ECSMemory::ComponentPools.end()) {
			n_PAllocator = new Memory::PoolAllocator();
			n_PAllocator->Init<T>(componentPoolSize, alignof(T));
			ECSMemory::ComponentPools.insert(std::make_pair(type, n_PAllocator));
		} else { // type is defined and we can set type
			n_PAllocator = it->second;
		}

		n_entity = GetEntity(entityID);
		n_component = new T();
		n_component->type = type;

		if(!n_component->Init(data)) {
			delete n_component;
			return nullptr;
		}

		n_entity->AddComponent(n_component);

		return n_component;
	}

	template<class T>
	T* ECSManager::GetComponent(EntityID entityID) const {
		return reinterpret_cast<T*>(GetEntity(entityID)->GetComponent<T>());
	}

	template<class T>
	T* ECSManager::CreateSystem() {
		T* n_system;

		n_system = new (ECSMemory::SystemPool) T();
		n_system->type = typeid(T).hash_code();
		m_systemsMap.insert(std::make_pair(n_system->type, n_system));

		return n_system;
	}

	template<class T>
	T* ECSManager::GetSystem() const {
		SystemMap::const_iterator it;
		SystemType type;

		type = typeid(T).hash_code();
		it = m_systemsMap.find(type);
		if (it != m_systemsMap.end()) {
			return (*it).second;
		}

		return nullptr;
	}
}}
