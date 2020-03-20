#pragma once

namespace Neon { namespace Memory {
	struct FreeBlock {
		/* Public Members */
		FreeBlock* next;
	};

	typedef FreeBlock* FreeList;
}}
