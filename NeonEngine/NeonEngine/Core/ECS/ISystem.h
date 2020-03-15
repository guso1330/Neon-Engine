#pragma once

#include "Core/Time/Timer.h"
#include "Core/ECS/ECSTypes.h"

namespace Neon { namespace ECS {
	struct ISystem {
		/* Constructor/Destructor */
		virtual ~ISystem() = default;

		inline void* operator new(size_t alloc_size) { return ::operator new(alloc_size); }
		inline void operator delete(void* deletePtr) { std::free(deletePtr); }
		void* operator new(size_t alloc_size, Memory::IAllocator& allocator) {
			void* return_address;

			return_address = allocator.Allocate(alloc_size);

			NE_ASSERT((return_address != nullptr), "System New: Memory address returned as nullptr");
			
			return return_address;
		}
		void operator delete(void* deletePtr, Memory::IAllocator& allocator) {
			allocator.Free(deletePtr);
		}

		/* Methods */
		virtual bool Init() = 0;
		virtual void Update(Timestep ts) = 0;

		SystemType type;
	};
}}
