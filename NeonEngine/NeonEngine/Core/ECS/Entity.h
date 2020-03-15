#pragma once

#include "Core/ECS/ECSTypes.h"
#include "Core/ECS/IComponent.h"

namespace Neon { namespace ECS {
	class Entity {
		public:
			/* Constructor/Destructor */
			explicit Entity(const EntityID id);

			/* Operator Overload */
			void* operator new (size_t alloc_size);
			void operator delete (void* deletePtr);

			/* Member Functions */
			void AddComponent(IComponent* component);

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
