#include "Core/Memory/IAllocator.h"
#include "Core/Core.h"

namespace Neon { namespace Memory {
	IAllocator::IAllocator() :
		m_start(nullptr),
		m_size(0),
		m_allocations(0),
		m_usedMemory(0)
	{}

	IAllocator::~IAllocator() {
		NE_CORE_ASSERT(
			m_usedMemory == 0 && m_allocations == 0,
			"IAllocator Destructor Failed. Memory still in use, please Free it"
		);
		m_size = 0;
		m_start = nullptr;
	}
}}
