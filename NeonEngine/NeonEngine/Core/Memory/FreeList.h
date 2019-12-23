#pragma once

namespace Neon { namespace Memory {
	struct FreeBlock {
		/* Constructor/Destructor */
		FreeBlock() {
			next = nullptr;
		}

		/* Public Members */
		FreeBlock* next;
	};

	typedef FreeBlock* FreeList;
}}
