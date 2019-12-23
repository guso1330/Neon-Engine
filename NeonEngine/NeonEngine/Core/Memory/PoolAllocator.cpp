#include "Core/Memory/PoolAllocator.h"

namespace Neon { namespace Memory {
	PoolAllocator::PoolAllocator() :
		m_alignment(0),
		m_blockSize(0),
		m_FreeHead(nullptr)
	{}

	PoolAllocator::~PoolAllocator() {
		// Clean up memory and freelist
		m_FreeHead = nullptr;
	}

	void* PoolAllocator::Allocate(size_t allocSize, uint8_t alignment) {

	}

	void PoolAllocator::Free(void* memptr) {

	}
}}
