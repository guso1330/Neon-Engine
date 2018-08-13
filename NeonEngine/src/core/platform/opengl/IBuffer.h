#pragma once

namespace neon {
	class IBuffer {
		public:
			IBuffer() {}

			virtual void Bind() = 0;
			virtual void Unbind() = 0;
	};
}

