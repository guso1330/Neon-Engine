#include "input.h"

namespace neon {
	// Input Class
	Input::Input() {
		m_eventManager = new EventManager();
		m_mouse = new Mouse();
		m_keyboard = new Keyboard();
	}

	Input::~Input() {}

	void Input::KeyboardEvent(const int key, const int action, const int mods) {
		if(action != NEON_KEY_UP) {
			m_keyboard->SetKey(key, true);
		} else {
			m_keyboard->SetKey(key, false);
		}
	}

	void Input::MouseEvent(const int button, const int action, const int mods) {
		if(action != NEON_BUTTON_UP) {
			m_mouse->SetButton(button, true);
		} else {
			m_mouse->SetButton(button, false);
		}
	}

	void Input::MouseCursorEvent(int x, int y) {
		m_mouse->SetPos(x, y);
	}
}