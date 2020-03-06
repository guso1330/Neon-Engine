#pragma once

#include "Core/Memory/IAllocator.h"
#include "Core/Memory/FreeList.h"

namespace Neon { namespace Memory {
	class PoolAllocator : public IAllocator {
		public:
			/* Constructor/Destructor */
			PoolAllocator();
			~PoolAllocator();


			/* Members */
			template<class T>
			bool Init(size_t numItems, uint8_t alignment = NE_DEFAULT_MEM_ALIGNMENT) {
				if (numItems > 0) {
					m_chunkSize = sizeof(T) > sizeof(FreeList) ? sizeof(T) : sizeof(FreeList);
					m_blockSize = (m_chunkSize * numItems) + alignment;
					m_alignment = alignment;
					m_pFreeListHead = AllocateBlock();
					m_size = m_blockSize;
					m_initialized = true;
					NE_CORE_INFO("PoolAllocator: Initialized with size of {} bytes, and alignment of {}", m_size, alignment);
				}

				return m_initialized;
			}
			virtual void* Allocate(size_t size);
			virtual void Free(void* deletePtr);

			/* Getters */
			inline const size_t GetSize() const { return m_size; }
			inline const size_t GetUsedMemory() const { return m_usedMemory; }

		private:
			FreeList AllocateBlock();

		private:
			bool m_initialized;
			uint8_t m_alignment;
			size_t m_blockSize;
			size_t m_chunkSize;
			size_t m_size;
			size_t m_usedMemory;
			FreeList m_pFreeListHead;
	};
}}
