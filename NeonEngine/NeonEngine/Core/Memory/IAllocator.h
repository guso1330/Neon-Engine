#pragma once

#include "nepch.h"
#include "Core/Core.h"

namespace Neon { namespace Memory {
	class IAllocator {
		public:
			/* Constructor/Destructor */
			IAllocator();
			virtual ~IAllocator();

			/* Members */
			virtual void* Allocate(size_t allocSize, uint8_t alignment = NE_DEFAULT_MEM_ALIGNMENT) = 0;
			virtual void Free(void* memptr) = 0;

			/* Getters */
			inline void* GetStart() const { return m_start; }
			inline size_t GetSize() const { return m_size; }
			inline size_t GetAllocations() const { return m_allocations; }
			inline size_t GetUsedMemory() const { return m_usedMemory; }

		protected:
			void* m_start;
			size_t m_size;
			size_t m_allocations;
			size_t m_usedMemory;
	};
}}
