#include "Core/ECS/ECSMemory.h"

namespace Neon { namespace ECS {
	Memory::PoolAllocator ECSMemory::EntityPool;
	Memory::PoolAllocator ECSMemory::SystemPool;
	ComponentPoolMap ECSMemory::ComponentPools;
}}
