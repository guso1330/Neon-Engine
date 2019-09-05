#pragma once


#include "eventManager.h"
#include "keyboard.h"
#include "mouse.h"

namespace Neon {

	enum EventType {
		NEON_KEY_EVENT,
		NEON_MOUSE_EVENT,
		NEON_CURSOR_EVENT,
		NEON_WINDOW_EVENT
	};

	class Input {

		public:
			Input();
			~Input();

			template<class T>
			void BindEvent(const char* name, EventType event_type, const T &callback) {
				if(m_eventManager.Register(name, callback)) {
					NE_CORE_INFO("InputManager: '{}' was registered", name);
				} else {
					NE_CORE_WARN("InputManager: '{}' was not registered and already exists");
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

			inline void PrintEvents() { m_eventManager.PrintEvents(); }

			// 
			// KEYBOARD
			//
			inline const bool IsKeyDown(int key) const { return m_keyboard.GetKey(key); }
			inline const bool IsKeyUp(int key)   const { return !m_keyboard.GetKey(key); }

			//
			// Mouse
			//
			inline const glm::vec2 GetCursorPosition()  const { return m_mouse.GetPosition(); }
			inline const bool IsMouseDown(int key) const { return m_mouse.GetButton(key); }
			inline const bool IsMouseUp(int key)   const { return !m_mouse.GetButton(key); }

		private:
			// Note: Each input class only has one associated mouse and keyboard
			Keyboard m_keyboard;
			Mouse m_mouse;
			EventManager m_eventManager;

			std::vector<const char*> m_keyboardEventNames;
			std::vector<const char*> m_mouseEventNames;
			std::vector<const char*> m_mouseCursorEventNames;
	};
}