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
			Func _f;

			Callback() {}
			Callback(Func f) { _f = f; }
			~Callback() {}

			void operator()(ArgTypes... args) { if(_f) _f(args...); }
	};
}
