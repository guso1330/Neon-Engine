#pragma once

#define MAX_KEYS 1024

#include "inputDevice.h"

#include <glm/glm.hpp>

#include <iostream>
#include <algorithm>

namespace neon {

	enum KeyEvents {
		NEON_KEY_UP,
		NEON_KEY_DOWN,
		NEON_KEY_HOLD
	};

	class Keyboard : public InputDevice {
		public:
			Keyboard();
			~Keyboard();

			inline bool GetKey(int key) { return m_keys[key]; }

			template<class... ArgTypes>
			void OnKeyEvent(int key, int action, int mod, ArgTypes... args) {
				if(action != NEON_KEY_UP) {
					m_keys[key] = true;
				} else {
					m_keys[key] = false;
				}

				Click key_call = std::make_tuple(key, action, mod);

				ClickEvent::const_iterator it = m_clickEvents.find(key_call);

				if(it != m_clickEvents.end()) {
					FireEvent(it->second, args...);
				}
			}

		private:
			bool m_keys[MAX_KEYS];
	};
}