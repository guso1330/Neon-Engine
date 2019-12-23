#pragma once

namespace Neon { namespace Memory {
	static void* GetForwardAlignedAddress(void* address, uint8_t alignment = 8) {
		uintptr_t addressNum = reinterpret_cast<uintptr_t>(address);
		uint8_t adjustedAlign = static_cast<uint8_t>(alignment - 1);
		return (void*) (
			(addressNum + adjustedAlign)
			& ~(adjustedAlign)
		);
	}

	static uint8_t GetForwardAlignedAddressOffset(void* address, uint8_t alignment = 8) {
		uint8_t adjustment = alignment - (
			reinterpret_cast<uintptr_t>(address)
			& static_cast<uintptr_t>(alignment - 1)
		);

		if (adjustment == alignment) return 0;

		return adjustment;
	}
}}
