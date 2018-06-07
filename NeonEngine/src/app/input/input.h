#pragma once

#include "eventManager.h"
#include "keyboard.h"
#include "mouse.h"

#include <vector>
#include <iterator>
#include <tuple>
#include <typeinfo>
#include <iostream>

namespace neon {

	enum EventType {
		NEON_KEY_EVENT,
		NEON_MOUSE_EVENT,
		NEON_CURSOR_EVENT
	};

	class Input {

		public:
			Input();
			~Input();

			template<class T>
			void BindEvent(const char* name, EventType event_type,const T &callback) {
				if(m_eventManager->Register(name, callback)) {
					std::cout << "InputManager: '" << name << "' was registered" << std::endl;
				} else {
					std::cout << "InputManager: '" << name << "' was not registered and already exists" << std::endl;
				}
				switch(event_type) {
					case NEON_KEY_EVENT:
						m_keyboardEventNames.push_back(name);
						break;
					case NEON_MOUSE_EVENT:
						m_mouseEventNames.push_back(name);
						break;
					case NEON_CURSOR_EVENT:
						m_mouseCursorEventNames.push_back(name);
						break;
					default:
						break;
				}
			}

			void FlushKeyboardEvents() const;
			void FlushMouseEvents() const;
			void FlushCursorEvents() const;

			void KeyboardEvent(const int key, const int action, const int mods);

			void MouseEvent(const int button, const int action, const int mods);

			void MouseCursorEvent(int x, int y);

			// 
			// KEYBOARD
			//
			const bool IsKeyDown(int key) const { return m_keyboard->GetKey(key); }
			const bool IsKeyUp(int key)   const { return !m_keyboard->GetKey(key); }

			//
			// Mouse
			//
			const glm::vec2 GetCursorPosition()  const { return m_mouse->GetPosition(); }
			const bool IsMouseDown(int key) const { return m_mouse->GetButton(key); }
			const bool IsMouseUp(int key)   const { return !m_mouse->GetButton(key); }

		private:
			// Note: Each input class only has one associated mouse and keyboard
			Keyboard *m_keyboard;
			Mouse *m_mouse;
			EventManager *m_eventManager;

			std::vector<const char*> m_keyboardEventNames;
			std::vector<const char*> m_mouseEventNames;
			std::vector<const char*> m_mouseCursorEventNames;
	};
}