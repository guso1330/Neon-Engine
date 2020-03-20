#pragma once

#include "Core/ECS/ECSTypes.h"
#include "Core/ECS/IComponent.h"

/*
	TODO:
	- Entity only supports one, create support for multiple components of type
*/

namespace Neon { namespace ECS {
	class Entity {
		public:
			/* Constructor/Destructor */
			explicit Entity(const EntityID id);

			/* Operator Overload */
			inline void* operator new(size_t alloc_size) { NE_CORE_ASSERT(false, "Entity: Cannot call new on Entity without allocator defined"); }
			void* operator new (size_t alloc_size, Memory::IAllocator& allocator);
			inline void operator delete(void* deletePtr) { NE_CORE_ASSERT(false, "Entity: Cannot call delete on Entity"); }

			/* Member Functions */
			void CreateComponent(IComponent* component);
			template<class T>
			T* RemoveComponent();

			/* Getters */
			inline const EntityID GetID() { return m_id; }
			template<class T>
			IComponent* GetComponent() const;

		private:
			EntityID m_id;
			ComponentMap m_componentMap;
	};
}}

#include "Core/ECS/Entity.tpp"
