#pragma once

#include "Core/Memory/IAllocator.h"
#include "Core/Memory/FreeList.h"

#include "Core/Core.h"
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
				uint8_t adjustment;
				// // Ensure size of T is greater than the size of a pointer, since empty blocks store the next address
				// NE_CORE_ASSERT(sizeof(T) >= sizeof(void*), "PoolAllocator - object size cannot be smaller than address size");

				if (numElements > 0) {
					m_blockSize = sizeof(T) > sizeof(FreeList) ? sizeof(T) : sizeof(FreeList);
					m_size = numElements * m_blockSize;
					m_alignment = alignof(T);
					m_start = new unsigned char[m_size];
					adjustment = GetForwardAlignedAddressOffset(m_start, m_alignment);
					m_FreeHead = (FreeList*)((uintptr_t)m_start + adjustment);

					for (int i = 0; i < numElements; ++i) {
						
					}

					NE_CORE_INFO("PoolAllocator: Initialized with size of {} bytes", m_size);
					return true;
				}

				return false;
			}

			virtual void* Allocate(size_t allocSize, uint8_t alignment = NE_DEFAULT_MEM_ALIGNMENT) override;
			virtual void Free(void* memptr) override;

			/* Getters */
			uint8_t GetAlignment() const { return m_alignment; }
			size_t GetBlockSize() const { return m_blockSize; }

		private:
			/* Constructor/Destructor */
			PoolAllocator(const PoolAllocator&);

			/* Operator overrides */
			PoolAllocator& operator=(const PoolAllocator&);

			/* Private Members */
			uint8_t m_alignment;
			size_t m_blockSize;
			FreeList* m_FreeHead;
	};
}}
