#pragma once

#include "keyboard.h"
#include "mouse.h"

#include <functional>
#include <iostream>

namespace neon {
	class Input {

		public:
			Input();
			~Input();

			template<class T>
			void BindKeyboardEvent(const char *name, int key, int action, int mods, const T &callback) {
				m_keyboard.BindClickEvent(name, key, action, mods, callback);
			}

			template<class T>
			void BindKeyboardEvent(const char *name, Click* clickEvents, int size, const T &callback) {
				std::vector<Click> clicks;
				clicks.assign(clickEvents, clickEvents + size);
				m_keyboard.BindClickEvent(name, clicks, callback);
			}

			template<class... ArgTypes>
			void KeyboardEvent(int key, int action, int mods, ArgTypes... args) {
				switch(action) {
					case NEON_KEY_UP:
						m_keyboard.OnKeyEvent(key, NEON_KEY_UP, mods);
						break;
					case NEON_KEY_DOWN:
						m_keyboard.OnKeyEvent(key, NEON_KEY_DOWN, mods);
						break;
					case NEON_KEY_HOLD:
						m_keyboard.OnKeyEvent(key, NEON_KEY_HOLD, mods);
						break;
					default:
						break;
				}	
			}

			bool IsKeyDown(int key) { return m_keyboard.GetKey(key); }
			bool IsKeyUp(int key) { return !m_keyboard.GetKey(key); }

		private:
			Keyboard m_keyboard;
			Mouse m_mouse;
	};
}