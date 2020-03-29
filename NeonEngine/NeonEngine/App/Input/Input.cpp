#include "nepch.h"

#include "Core/Events/EventManager.h"
#include "Core/Events/EventTypes.h"
#include "App/Input/Input.h"

namespace Neon {

	Timer Input::s_Timer;

	// Input Class
	Input::Input() {
		s_Timer.Init();
	}

	void Input::KeyboardEvent(const int key, const int scancode, const int action, const int mods) {
		std::function<void(std::string)> callEventManagerFn = [key, scancode, action, mods](std::string type) {
			EventManager::GetInstance().DispatchEvent(type, key, scancode, action, mods);
		};

		if(action != NEON_KEY_UP) {
			m_Keyboard.SetKey(key, true);
			callEventManagerFn(NEON_EVENT_KEY_DOWN);
		} else if (action == NEON_KEY_HOLD) {
			// TODO: Get key hold to work
			m_Keyboard.SetKey(key, true);
			callEventManagerFn(NEON_EVENT_KEY_HOLD);
		} else {
			m_Keyboard.SetKey(key, false);
			callEventManagerFn(NEON_EVENT_KEY_RELEASE);
		}

		callEventManagerFn(NEON_EVENT_KEY_PRESS);

		s_Timer.Tick();
	}

	void Input::MousePressEvent(const int button, const int action, const int mods) {
		std::function<void(std::string)> callEventManagerFn = [button, action, mods](std::string type) {
			EventManager::GetInstance().DispatchEvent(type, button, action, mods);
		};

		if(action != NEON_BUTTON_UP) {
			m_Mouse.SetButton(button, true);
			callEventManagerFn(NEON_EVENT_MOUSE_DOWN);
		} else {
			m_Mouse.SetButton(button, false);
			callEventManagerFn(NEON_EVENT_MOUSE_RELEASE);
		}
		// TODO: Add mouse hold

		callEventManagerFn(NEON_EVENT_MOUSE_PRESS);

		s_Timer.Tick();
	}

	void Input::MouseCursorEvent(int x, int y) {
		m_Mouse.SetPosition(x, y);

		EventManager::GetInstance().DispatchEvent(NEON_EVENT_MOUSE_CURSOR, x, y);

		s_Timer.Tick();
	}

	void Input::MouseScrollEvent(int xOffset, int yOffset) {
		EventManager::GetInstance().DispatchEvent(NEON_EVENT_MOUSE_SCROLL, xOffset, yOffset);

		s_Timer.Tick();
	}
}
