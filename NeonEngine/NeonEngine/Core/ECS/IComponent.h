#pragma once

#include "Core/ECS/ECSTypes.h"
#include "Core/ECS/ECSMemory.h"

/*
	TODO:
	- Could possibly split out the memory functions into a generic class
*/

namespace Neon { namespace ECS {
	struct IComponent {
		/* Constructor/Destructor */
		IComponent() = default;
		virtual ~IComponent() = default;

		/* Operator Overloads */
		inline void* operator new(size_t alloc_size) { return ::operator new(alloc_size); }
		inline void operator delete(void* deletePtr) { std::free(deletePtr); }
		void* operator new(size_t alloc_size, Memory::IAllocator& allocator) {
			void* return_address;

			return_address = allocator.Allocate(alloc_size);

			NE_ASSERT((return_address != nullptr), "Component New: Memory address returned as nullptr");
			
			return return_address;
		}
		void operator delete(void* deletePtr, Memory::IAllocator& allocator) {
			allocator.Free(deletePtr);
		}

		/* Methods */
		virtual bool Init(void* data) = 0;

		/* Member Variables */
		ComponentType type;
	};
}}
