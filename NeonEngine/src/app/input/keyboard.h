#pragma once

#define MAX_KEYS 1024

#include "inputDevice.h"

#include <glm/glm.hpp>

#include <iostream>
#include <map>
#include <iterator>
#include <tuple>

namespace neon {

	enum KeyEvents {
		NEON_KEY_UP,
		NEON_KEY_DOWN,
		NEON_KEY_HOLD
	};

	typedef std::map<std::tuple<int, int, int>, const char*> KeyboardEventMap;

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

				std::tuple<int, int, int> key_call = std::make_tuple(key, action, mod);

				KeyboardEventMap::const_iterator it = m_keyboardEventsMap.find(key_call);

				if(it != m_keyboardEventsMap.end()) {
					// std::cout << (*it).second << std::endl;
					FireEvent((*it).second, args...);
				}
			}

			template<class T>
			void BindKeyboardEvent(const char* name, int key, int action, int mods, const T &callback) {
				if(BindEvent(name, callback)) {
					m_keyboardEventsMap.insert(
						std::make_pair(
							std::make_tuple(key, action, mods),
							name
						)
					);
				}
			}

		private:
			bool m_keys[MAX_KEYS];
			KeyboardEventMap m_keyboardEventsMap;
	};
}