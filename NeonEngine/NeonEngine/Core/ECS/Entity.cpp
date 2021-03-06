#include "Core/ECS/Entity.h"
#include "Core/ECS/ECSMemory.h"
#include "Core/Core.h"

namespace Neon { namespace ECS {
	Entity::Entity(const EntityID id) :
		m_id(id)
	{}

	void* Entity::operator new (size_t alloc_size, Memory::IAllocator& allocator) {
		void* return_address = allocator.Allocate(alloc_size);

		NE_ASSERT((return_address != nullptr), "Entity New: Memory address returned as nullptr");

		return return_address;
	}

	void Entity::CreateComponent(IComponent* component) {
		ComponentType type;
		ComponentMap::const_iterator it;

		type = component->type;
		it = m_componentMap.find(component->type);

		if (it == m_componentMap.end()) {
			m_componentMap.insert(std::make_pair(type, component));
		}
	}
}}
