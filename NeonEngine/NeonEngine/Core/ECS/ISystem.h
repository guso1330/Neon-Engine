#pragma once

#include "Core/Memory/IAllocator.h"
#include "Core/Time/Timer.h"
#include "Core/ECS/ECSTypes.h"
#include "Core/Core.h"

namespace Neon { namespace ECS {
	struct ISystem {
		/* Constructor/Destructor */
		virtual ~ISystem() = default;

		inline void* operator new(size_t alloc_size) { NE_CORE_ASSERT(false, "ISystem: Cannot call new on ISystem without allocator defined"); }
		inline void* operator new(size_t alloc_size, Memory::IAllocator& allocator) {
			void* return_address;

			return_address = allocator.Allocate(alloc_size);

			NE_ASSERT((return_address != nullptr), "System New: Memory address returned as nullptr");
			
			return return_address;
		}
		inline void operator delete(void* deletePtr) { NE_CORE_ASSERT(false, "ISystem: Cannot call delete on ISystem"); }

		/* Methods */
		virtual bool Init() = 0;
		virtual void Update(Timestep ts) = 0;

		SystemType type;
	};
}}
