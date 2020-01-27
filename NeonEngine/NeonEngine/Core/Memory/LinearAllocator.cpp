#include "Core/Core.h"

#include "Core/Memory/LinearAllocator.h"
#include "Core/Memory/Helpers.h"

namespace Neon { namespace Memory {
	LinearAllocator::LinearAllocator() {}

	LinearAllocator::~LinearAllocator() {
		m_currentAddressPosition = nullptr;
	}

	bool LinearAllocator::Init(size_t size) {
		if (size > 0) {
			m_size = size;
			m_start = new unsigned char[m_size];
			m_currentAddressPosition = m_start;
			NE_CORE_INFO("LinearAllocator: Initialized with size of {} bytes", m_size);
			return true;
		}
		return false;
	}

	void* LinearAllocator::Allocate(size_t allocSize, uint8_t alignment) {
		uintptr_t aligned_mem;
		uint8_t adjustment = GetForwardAlignedAddressOffset(m_currentAddressPosition, alignment);
		size_t n_usedMemory = GetUsedMemory() + adjustment + allocSize;

		NE_CORE_ASSERT(allocSize > 0 && GetSize() > 0, "LinearAllocator Allocate() - allocSize must be greater than 0");

		if (n_usedMemory > GetSize()) {
			NE_CORE_WARN("LinearAllocator: Cannot allocate anymore memory within reserved area. Call Clean()");
			return nullptr;
		}

		aligned_mem = (uintptr_t)m_currentAddressPosition + adjustment;

		// Set all private members
		m_currentAddressPosition = (void*)(aligned_mem + allocSize);
		++m_allocations;
		m_usedMemory = n_usedMemory;

		return (void*)aligned_mem;
	}

	void LinearAllocator::Free(void* memptr) {
		NE_CORE_ASSERT(false, "LinearAllocate Free failed. Please use Clean()");
	}

	void LinearAllocator::Clean() {
		m_allocations = m_usedMemory = 0;
		m_currentAddressPosition = m_start;
	}
}}
