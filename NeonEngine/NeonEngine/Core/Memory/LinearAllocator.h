#pragma once

#include "Core/Memory/IAllocator.h"

namespace Neon { namespace Memory {
	class LinearAllocator : public IAllocator {
		public:
			/* Constructor/Destructor */
			LinearAllocator();
			~LinearAllocator();

			/* Member Functions */
			virtual bool Init(size_t size, uint8_t alignment = NE_DEFAULT_MEM_ALIGNMENT);
			virtual void* Allocate(size_t size) override;
			virtual void Free(void* deletePtr) override;
			virtual void Clean();

			/* Getters */
			inline const size_t GetSize() const override { return m_size; }
			inline const size_t GetUsedMemory() const override { return m_usedMemory; }

		private:
			bool m_initialized;
			uint8_t m_alignment;
			size_t m_size;
			size_t m_usedMemory;
			void* m_pCurrentAddressPosition;
			void* m_pStart;
	};
}}
