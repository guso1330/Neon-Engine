#include "gtest/gtest.h"
#include "Core/Memory/LinearAllocator.h"

namespace Neon { namespace Memory {
	// class LinearAllocatorTest : public ::testing::Test {
	// 	protected:
	// 		bool InitializeAllocator(size_t size) {
	// 			return linearAlloc.Init(size);
	// 		}

	// 		void CleanAllocator() {
	// 			linearAlloc.Clean();
	// 		}

	// 		LinearAllocator linearAlloc;
	// };
	
	// TEST_F(LinearAllocatorTest, Init) {
	// 	size_t alloc_size = 512;
	// 	bool initialized = InitializeAllocator(alloc_size); // declare linear allocator of 512 bytes

	// 	ASSERT_TRUE(linearAlloc.GetSize() == alloc_size);
	// 	ASSERT_TRUE(initialized);

	// 	CleanAllocator();
	// }

	// TEST_F(LinearAllocatorTest, FailingInit) {
	// 	bool initialized = InitializeAllocator(0);
	// 	ASSERT_FALSE(initialized);
	// }

	// TEST_F(LinearAllocatorTest, Allocate) {
	// 	size_t alloc_size = 512;
	// 	bool initialized = InitializeAllocator(alloc_size);
	// 	void* allocated_address = nullptr;

	// 	NE_CORE_WARN("LinearAllocatorTest: Allocating 4 ints with proper alignment");

	// 	allocated_address = linearAlloc.Allocate(4 * sizeof(int), alignof(int));

	// 	ASSERT_TRUE(linearAlloc.GetUsedMemory() == 4 * sizeof(int));
	// 	ASSERT_TRUE(allocated_address != nullptr);

	// 	CleanAllocator();
	// }
}}
