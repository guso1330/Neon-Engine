#pragma once

#include "Core/Core.h"

namespace Neon { namespace Memory {
	static size_t GetAlign(size_t n) {
		return (n + sizeof(intptr_t) - 1) & ~(sizeof(intptr_t) - 1);
	}

	static void* GetForwardAlignedAddress(void* address, uint8_t alignment = NE_DEFAULT_MEM_ALIGNMENT) {
		uintptr_t addressNum = reinterpret_cast<uintptr_t>(address);
		uint8_t adjustedAlign = static_cast<uint8_t>(alignment - 1);
		return (void*) (
			(addressNum + adjustedAlign)
			& ~(adjustedAlign)
		);
	}

	static uint8_t GetForwardAlignedAddressOffset(void* address, uint8_t alignment = NE_DEFAULT_MEM_ALIGNMENT) {
		uint8_t adjustment = alignment - (
			reinterpret_cast<uintptr_t>(address)
			& static_cast<uintptr_t>(alignment - 1)
		);

		if (adjustment == alignment) return 0;

		return adjustment;
	}
}}
