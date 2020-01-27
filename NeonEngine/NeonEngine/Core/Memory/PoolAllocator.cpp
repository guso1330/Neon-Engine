#include "Core/Memory/PoolAllocator.h"

namespace Neon { namespace Memory {
	/*
		TODO
		- Handle allocation differently
		- Support creation of multiple pools and when allocations are full create more pools
	*/

	PoolAllocator::PoolAllocator() :
		m_blockSize(0),
		m_pFreeHead(nullptr)
	{}

	PoolAllocator::~PoolAllocator() {
		// Clean up memory and freelist
		m_pFreeHead = m_pPoolHead = nullptr;
		m_usedMemory = m_allocations = 0;
	}

	void* PoolAllocator::Allocate(size_t allocSize, uint8_t alignment) {
		FreeList c_block = m_pFreeHead;
		if (c_block == nullptr) {
			// TODO: Handle running out of space in a different way
			// NE_CORE_ASSERT(false, "PoolAllocator - There are no more free blocks available");
			return nullptr;
		}

		m_pFreeHead = c_block->next;

		++m_allocations;

		return c_block;
	}

	void PoolAllocator::Free(void* memptr) {
		// TODO: need to check that the memptr is in the range of the memory block
		reinterpret_cast<FreeList>(memptr)->next = m_pFreeHead;
		m_pFreeHead = reinterpret_cast<FreeList>(memptr);

		--m_allocations;
	}
}}
