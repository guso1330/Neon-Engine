#pragma once

#include "nepch.h"

namespace Neon {
	class BaseCallback {
		public:
			virtual ~BaseCallback() {}
	};

	template<class... ArgTypes>
	class Callback : public BaseCallback {
		typedef std::function<void(ArgTypes...)> Func;

		public:
			Callback() {}
			Callback(Func func) { m_func = func; }
			~Callback() {}

			void operator()(ArgTypes... args) { if(m_func) m_func(args...); }
		private:
			Func m_func;
	};
}
