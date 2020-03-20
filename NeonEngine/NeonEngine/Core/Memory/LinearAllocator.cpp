#include "Core/Core.h"

#include "Core/Memory/LinearAllocator.h"
#include "Core/Memory/Helpers.h"

namespace Neon { namespace Memory {
	LinearAllocator::LinearAllocator() : m_initialized(false) {}

	LinearAllocator::~LinearAllocator() {
		m_usedMemory = 0;
		m_size = 0;
		m_pCurrentAddressPosition = nullptr;
	}

	bool LinearAllocator::Init(size_t size, uint8_t alignment) {
		if (size > 0) {
			m_size = size;
			m_alignment = alignment;
			m_pStart = m_pCurrentAddressPosition = new unsigned char[size + alignment];
			m_initialized = true;
			NE_CORE_INFO("LinearAllocator: Initialized with size of {} bytes, and alignment of {}", m_size, alignment);
		}
	
		return m_initialized;
	}

	void* LinearAllocator::Allocate(size_t size) {
		uintptr_t aligned_mem;
		uint8_t adjustment;
		size_t n_usedMemory;

		NE_CORE_ASSERT(m_initialized, "LinearAllocator Allocate() - cannot call allocate on uninitialized LinearAllocator");
		NE_CORE_ASSERT(size > 0 && GetSize() > 0, "LinearAllocator Allocate() - size must be greater than 0");

		adjustment = GetForwardAlignedAddressOffset(m_pCurrentAddressPosition, m_alignment);
		n_usedMemory = GetUsedMemory() + adjustment + size;
		// NE_CORE_WARN("LinearAllocator n_usedMemory = {}", n_usedMemory);

		if (n_usedMemory > GetSize()) {
			NE_CORE_WARN("LinearAllocator: Cannot allocate anymore memory within reserved area. Call Clean()");
			return nullptr;
		}

		aligned_mem = (uintptr_t)m_pCurrentAddressPosition + adjustment;

		// Set all private members
		m_pCurrentAddressPosition = (void*)(aligned_mem + size);
		m_usedMemory = n_usedMemory;

		return (void*)aligned_mem;
	}

	void LinearAllocator::Free(void* deletePtr) {
		NE_CORE_ASSERT(false, "LinearAllocate Free failed. Please use Clean()");
	}

	void LinearAllocator::Clean() {
		NE_CORE_ASSERT(m_initialized, "LinearAllocator Allocate() - cannot call allocate on uninitialized LinearAllocator");
		m_usedMemory = 0;
		m_pCurrentAddressPosition = m_pStart;
	}
}}
