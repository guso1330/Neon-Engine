#include "nepch.h"

#include "Core/Events/EventManager.h"
#include "Core/Events/EventTypes.h"
#include "App/Input/Input.h"

namespace Neon {

	Timer Input::s_Timer;

	// Input Class
	Input::Input() {
		InitEvents();
		s_Timer.Init();
	}

	void Input::KeyboardEvent(const int key, const int action, const int mods) {
		if(action != NEON_KEY_UP) {
			m_Keyboard.SetKey(key, true);
		} else {
			m_Keyboard.SetKey(key, false);
		}

		EventManager::DispatchEvent(NEON_EVENT_KEY_PRESS, key, action, mods);

		s_Timer.Tick();
	}

	void Input::MousePressEvent(const int button, const int action, const int mods) {
		if(action != NEON_BUTTON_UP) {
			m_Mouse.SetButton(button, true);
		} else {
			m_Mouse.SetButton(button, false);
		}

		EventManager::DispatchEvent(NEON_EVENT_MOUSE_PRESS, button, action, mods);

		s_Timer.Tick();
	}

	void Input::MouseCursorEvent(int x, int y) {
		m_Mouse.SetPosition(x, y);

		EventManager::DispatchEvent(NEON_EVENT_MOUSE_CURSOR, x, y);

		s_Timer.Tick();
	}

	void Input::InitEvents() {
		EventManager::AddEvent(NEON_EVENT_KEY_PRESS, EventPtr(new KeyPressEvent()));
		EventManager::AddEvent(NEON_EVENT_MOUSE_PRESS, EventPtr(new struct MousePressEvent()));
		EventManager::AddEvent(NEON_EVENT_MOUSE_CURSOR, EventPtr(new struct MouseCursorEvent()));
	}
}
