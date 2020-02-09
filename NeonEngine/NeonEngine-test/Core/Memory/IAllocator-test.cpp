#include "gtest/gtest.h"
#include "Core/Memory/IAllocator.h"

namespace Neon { namespace Memory {
	class TestAllocator : public IAllocator {
		public:
			virtual void* Allocate(size_t allocSize, uint8_t alignment = NE_DEFAULT_MEM_ALIGNMENT);
			virtual void Free(void* memptr);
	};

	TEST(IAllocatorTest, test1) {
		// EXPECT_EQ(Formula::bla (0),  0);
	}
}}
