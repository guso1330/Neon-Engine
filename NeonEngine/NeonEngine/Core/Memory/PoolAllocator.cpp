#include "Core/Memory/PoolAllocator.h"

namespace Neon { namespace Memory {
	PoolAllocator::PoolAllocator() :
		m_blockSize(0),
		m_FreeHead(nullptr)
	{}

	PoolAllocator::~PoolAllocator() {
		// Clean up memory and freelist
		m_FreeHead = nullptr;
	}

	void* PoolAllocator::Allocate(size_t allocSize, uint8_t alignment) {
		FreeList c_block = m_FreeHead;
		if (c_block == nullptr) {
			// TODO: Handle running out of space in a different way
			NE_CORE_ASSERT(false, "PoolAllocator: There are no more free blocks available");
			return nullptr;
		}

		m_FreeHead = c_block->next;

		return c_block;
	}

	void PoolAllocator::Free(void* memptr) {
		reinterpret_cast<FreeList>(memptr)->next = m_FreeHead;

		// And the allocation pointer is now set
		// to the returned (free) chunk:

		m_FreeHead = reinterpret_cast<FreeList>(memptr);
	}
}}
