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

	class Input {

		public:
			Input();
			~Input();

			template<class T>
			void BindEvent(const char* name, const T &callback) {
				m_eventNames.push_back(name);
				if(m_eventManager->Register(name, callback)) {
					std::cout << "InputManager: '" << name << "' was registered" << std::endl;
				} else {
					std::cout << "InputManager: '" << name << "' was not registered and already exists" << std::endl;
				}
			}

			void FlushEvents() const {
				for(int i=0; i < m_eventNames.size(); ++i) {
					m_eventManager->Run(m_eventNames[i]);
				}
			}

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
			const glm::vec2 GetCursorPos()  const { return m_mouse->GetPos(); }
			const bool IsMouseDown(int key) const { return m_mouse->GetButton(key); }
			const bool IsMouseUp(int key)   const { return !m_mouse->GetButton(key); }

		private:
			// Note: Each input class only has one associated mouse and keyboard
			Keyboard *m_keyboard;
			Mouse *m_mouse;
			EventManager *m_eventManager;

			std::vector<const char*> m_eventNames;
	};
}