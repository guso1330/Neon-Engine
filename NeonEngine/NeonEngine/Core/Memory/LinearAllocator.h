#pragma once

#include "Core/Memory/IAllocator.h"

namespace Neon { namespace Memory {
	class LinearAllocator : public IAllocator {
		public:
			/* Constructor/Destructor */
			LinearAllocator();
			~LinearAllocator();

			/* Member Functions */
			virtual bool Init(size_t size);
			virtual void* Allocate(size_t allocSize, uint8_t alignment = NE_DEFAULT_MEM_ALIGNMENT) override;
			virtual void Free(void* memptr) override;
			virtual void Clean();

		private:
			/* Constructor/Destructor */
			LinearAllocator(const LinearAllocator&);

			/* Operator overrides */
			LinearAllocator& operator=(const LinearAllocator&);

			void* m_currentAddressPosition;
	};
}}
