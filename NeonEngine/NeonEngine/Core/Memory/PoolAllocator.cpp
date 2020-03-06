#include "Core/Memory/PoolAllocator.h"

#include "Core/Memory/Helpers.h"

namespace Neon { namespace Memory {
	PoolAllocator::PoolAllocator() :
		m_initialized(false),
		m_chunkSize(0),
		m_blockSize(0),
		m_size(0),
		m_usedMemory(0),
		m_pFreeListHead(nullptr)
	{}

	PoolAllocator::~PoolAllocator() {
		m_size = 0;
		m_usedMemory = 0;
		m_chunkSize = 0;
		m_blockSize = 0;
		m_pFreeListHead = nullptr;
		m_initialized = false;
	}

	void* PoolAllocator::Allocate(size_t size) {
        FreeList n_freeList;

		NE_CORE_ASSERT(m_initialized, "PoolAllocator Allocate() - cannot call allocate on uninitialized PoolAllocator");

		if (m_pFreeListHead == nullptr) {
			m_pFreeListHead = AllocateBlock();
		}

		n_freeList = m_pFreeListHead;
		m_pFreeListHead = m_pFreeListHead->next;

		m_usedMemory += m_chunkSize;

		return reinterpret_cast<void*>(n_freeList);
	}

	void PoolAllocator::Free(void* deletePtr) {
		reinterpret_cast<FreeList>(deletePtr)->next = m_pFreeListHead;
		m_pFreeListHead = reinterpret_cast<FreeList>(deletePtr);
		m_usedMemory -= m_chunkSize;
	}

	FreeList PoolAllocator::AllocateBlock() {
		FreeList n_freeList = nullptr;
		FreeList n_chunk = nullptr;
		uint8_t adjustment = 0;
		size_t numItems = 0;

		n_freeList = reinterpret_cast<FreeList>(new unsigned char[m_blockSize]);
		n_chunk = n_freeList;
		numItems = m_blockSize / m_chunkSize;

		for (int i = 0; i < numItems - 1; ++i) {
			adjustment = GetForwardAlignedAddressOffset(reinterpret_cast<void*>(n_chunk), m_alignment);
			n_chunk->next = reinterpret_cast<FreeList>(
				reinterpret_cast<unsigned char*>(n_chunk) + m_chunkSize + adjustment
			);
			n_chunk = n_chunk->next;
		}

		n_chunk->next = nullptr;
		m_size += m_blockSize;

		return n_freeList;
	}
}}
