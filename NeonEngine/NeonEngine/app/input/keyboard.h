#pragma once

#define MAX_KEYS 1024

#include <glm/glm.hpp>

#include <iostream>
#include <algorithm>

namespace neon {

	enum KeyEvents {
		NEON_KEY_UP,
		NEON_KEY_DOWN,
		NEON_KEY_HOLD
	};

	class Keyboard {
		public:
			Keyboard();

			~Keyboard();

			inline const bool GetKey(const int key) const { return m_keys[key]; }
			inline void SetKey(const int key, const bool state) { m_keys[key] = state; }

			// template<class... ArgTypes>
			// void OnKeyEvent(int key, int action, int mod, ArgTypes... args) {
			// 	Click key_call = std::make_tuple(key, action, mod);

			// 	ClickEvent::const_iterator it = m_clickEvents.find(key_call);

			// 	if(it != m_clickEvents.end()) {
			// 		FireEvent(it->second, args...);
			// 	}
			// }

		private:
			bool m_keys[MAX_KEYS];
	};
}