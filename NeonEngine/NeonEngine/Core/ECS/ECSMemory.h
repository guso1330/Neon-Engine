#pragma once

#include "Core/Memory/PoolAllocator.h"
#include "Core/ECS/ECSTypes.h"
#include "nepch.h"

namespace Neon { namespace ECS {
	typedef std::map<ComponentType, Memory::PoolAllocator*> ComponentPoolMap;

	struct ECSMemory {
		static Memory::PoolAllocator EntityPool;
		static Memory::PoolAllocator SystemPool;
		static ComponentPoolMap ComponentPools;
	};
}}
