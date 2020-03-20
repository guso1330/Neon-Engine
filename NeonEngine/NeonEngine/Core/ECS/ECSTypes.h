#pragma once

#include "nepch.h"

namespace Neon { namespace ECS {
	class Entity;
	class IComponent;
	class ISystem;

	typedef unsigned int EntityID;
	typedef size_t ComponentType;
	typedef size_t SystemType;
	typedef std::map<EntityID, Entity*> EntityMap;
	typedef std::map<ComponentType, IComponent*> ComponentMap; // Limits one component of type
	typedef std::map<SystemType, ISystem*> SystemMap; // Limits one system of type

	namespace Type {
		template<class T>
		static inline size_t GetType() { return typeid(T).hash_code(); }
	}
}}
