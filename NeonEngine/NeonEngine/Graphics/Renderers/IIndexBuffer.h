#pragma once

namespace Neon {
	class IIndexBuffer {
		public:
			/* Constructors */
			virtual ~IIndexBuffer() = default;

			/* Methods */
			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;

			/* Getters */
			virtual const unsigned int GetCount() const = 0;

			static IIndexBuffer* Create(unsigned int* data, size_t size);
	};
} // Neon
