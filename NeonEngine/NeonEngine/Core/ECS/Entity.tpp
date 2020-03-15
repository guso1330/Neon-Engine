namespace Neon { namespace ECS {
	template<class T>
	IComponent* Entity::GetComponent() const {
		ComponentMap::const_iterator it = m_componentMap.find(typeid(T).hash_code());
		if (it != m_componentMap.end()) {
			return it->second;
		}

		return nullptr;
	}
}}
