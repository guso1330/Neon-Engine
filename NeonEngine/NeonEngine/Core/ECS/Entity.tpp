namespace Neon { namespace ECS {
	template<class T>
	T* Entity::RemoveComponent() {
		T* d_component;
		ComponentMap::iterator it;

		it = m_componentMap.find(Type::GetType<T>());
		if (it != m_componentMap.end()) {
			d_component = reinterpret_cast<T*>(it->second);
			m_componentMap.erase(it);
		}

		return d_component;
	}

	template<class T>
	IComponent* Entity::GetComponent() const {
		ComponentMap::const_iterator it = m_componentMap.find(Type::GetType<T>());
		if (it != m_componentMap.end()) {
			return it->second;
		}

		return nullptr;
	}
}}
