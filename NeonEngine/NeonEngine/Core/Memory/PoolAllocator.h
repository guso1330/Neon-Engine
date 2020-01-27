#pragma once

#include "Core/Memory/IAllocator.h"
#include "Core/Memory/FreeList.h"

#include "Core/Memory/Helpers.h"

namespace Neon { namespace Memory {
	class PoolAllocator : public IAllocator {
		public:
			/* Constructor/Destructor */
			PoolAllocator();
			~PoolAllocator();

			/* Member Functions */
			template<class T>
			bool Init(size_t numElements) {
				FreeList c_block;
				uint8_t adjustment;

				if (numElements > 0) {
					m_blockSize = sizeof(T) > sizeof(FreeList) ? sizeof(T) : sizeof(FreeList);
					m_size = numElements * m_blockSize;
					m_start = new unsigned char[m_size];
					adjustment = GetForwardAlignedAddressOffset(m_start, alignof(T));
					m_pFreeHead = m_pPoolHead = reinterpret_cast<FreeList>(
						reinterpret_cast<uintptr_t>(m_start) + adjustment
					);

					NE_CORE_WARN("PoolAllocator: adjustment - {}, alignment - {}", adjustment, GetAlign(sizeof(T)));

					// Set up the inherited member variables
					m_usedMemory = m_size + adjustment;

					c_block = m_pFreeHead;
					for (int i = 0; i < numElements; ++i) {
						adjustment = GetForwardAlignedAddressOffset(c_block , alignof(T));
						c_block->next = reinterpret_cast<FreeList>(
							reinterpret_cast<uintptr_t>(c_block) + m_blockSize + adjustment
						);
						c_block = c_block->next;
					}

					c_block->next = nullptr;

					NE_CORE_INFO("PoolAllocator: Initialized with size of {} bytes", m_size);

					return true;
				}

				return false;
			}

			virtual void* Allocate(size_t allocSize = 0, uint8_t alignment = NE_DEFAULT_MEM_ALIGNMENT) override;
			virtual void Free(void* memptr) override;

			/* Getters */
			size_t GetBlockSize() const { return m_blockSize; }

		private:
			/* Constructor/Destructor */
			PoolAllocator(const PoolAllocator&);

			/* Operator overrides */
			PoolAllocator& operator=(const PoolAllocator&);

			/* Private Members */
			size_t m_blockSize; // Size of individual blocks of memory
			FreeList m_pFreeHead; // Beginning of free list
			FreeList m_pPoolHead; // Beginning of pool
	};
}}
