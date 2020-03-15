#pragma once

namespace Neon {
	class Singleton {
		public:
			/* Constructor & Destructor */
			Singleton(const Singleton&) = delete;
			
			/* Operator Overrides */
			void operator=(Singleton const&) = delete;

		protected:
			Singleton() = default;
	};
}
