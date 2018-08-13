#pragma once

namespace neon {
	class IBuffer {
		public:
			IBuffer() {}

			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
	};
}

