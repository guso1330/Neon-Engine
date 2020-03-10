#pragma once

#include "Core/ECS/ECSTypes.h"
#include "Core/ECS/IComponent.h"
#include "nepch.h"

namespace Neon { namespace ECS {
	class Entity {
		public:
			explicit Entity(const EntityID id) : m_id(id) {  }

			/* Getters */
			inline const EntityID GetID() { return m_id; }
			template<class ComponentType>
			ComponentType* GetComponent() const {
				std::unordered_map<ComponentID, IComponent*>::const_iterator it = m_components.find(ComponentType::id);
				if (it != m_components.end()) {
					return it->second;
				}

				return nullptr;
			}

		private:
			EntityID m_id;
			std::unordered_map<ComponentID, IComponent*> m_components;
	};
}}
