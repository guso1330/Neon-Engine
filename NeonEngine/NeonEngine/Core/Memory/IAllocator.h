#pragma once

#include "nepch.h"
#include "Core/Core.h"

/*
	- Article for STL Aligned Memory Allocator: https://johanmabille.github.io/blog/2014/12/06/aligned-memory-allocator/
	- Article describing Custom Allocator creation: https://docs.roguewave.com/sourcepro/11.1/html/toolsug/11-6.html

	TODO:
	- For all allocators go through and verify that alignment is working
*/

namespace Neon { namespace Memory {
	class IAllocator {
		public:
			/* Constructor/Destructor */
			IAllocator() = default;
			IAllocator(const IAllocator& allocator) noexcept;
			IAllocator(IAllocator&& allocator) noexcept;
			virtual ~IAllocator() = default;

			/* Operator Override */
			IAllocator& operator=(const IAllocator& allocator) = delete;
			IAllocator& operator=(IAllocator&& allocator) noexcept;

			/* Members */
			virtual void* Allocate(size_t size) = 0;
			virtual void Free(void* deletePtr) = 0;

			/* Getters */
			virtual const size_t GetSize() const = 0;
			virtual const size_t GetUsedMemory() const = 0;

	};
}}
