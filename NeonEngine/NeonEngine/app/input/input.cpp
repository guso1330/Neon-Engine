#include "nepch.h"

#include "input.h"
#include "../eventManager.h"
#include "../eventTypes.h"

namespace Neon {
	// Input Class
	Input::Input() {
		InitEvents();
	}

	void Input::KeyboardEvent(const int key, const int action, const int mods) {
		if(action != NEON_KEY_UP) {
			m_keyboard.SetKey(key, true);
		} else {
			m_keyboard.SetKey(key, false);
		}

		EventManager::DispatchEvent(NEON_EVENT_KEY_PRESS, key, action, mods);
	}

	void Input::MousePressEvent(const int button, const int action, const int mods) {
		if(action != NEON_BUTTON_UP) {
			m_mouse.SetButton(button, true);
		} else {
			m_mouse.SetButton(button, false);
		}

		EventManager::DispatchEvent(NEON_EVENT_MOUSE_PRESS, button, action, mods);
	}

	void Input::MouseCursorEvent(int x, int y) {
		m_mouse.SetPosition(x, y);

		EventManager::DispatchEvent(NEON_EVENT_MOUSE_CURSOR, x, y);
	}

	void Input::InitEvents() {
		EventManager::AddEvent(NEON_EVENT_KEY_PRESS, EventPtr(new KeyPressEvent()));

		EventManager::AddEvent(NEON_EVENT_MOUSE_PRESS, EventPtr(new struct MousePressEvent()));

		EventManager::AddEvent(NEON_EVENT_MOUSE_CURSOR, EventPtr(new struct MouseCursorEvent()));
	}
}
