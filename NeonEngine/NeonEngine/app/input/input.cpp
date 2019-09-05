#include "nepch.h"

#include "input.h"

namespace Neon {

	// Input Class
	Input::Input() {}

	Input::~Input() {}

	void Input::KeyboardEvent(const int key, const int action, const int mods) {
		if(action != NEON_KEY_UP) {
			m_keyboard.SetKey(key, true);
		} else {
			m_keyboard.SetKey(key, false);
		}

		FlushKeyboardEvents();
	}

	void Input::MouseEvent(const int button, const int action, const int mods) {
		if(action != NEON_BUTTON_UP) {
			m_mouse.SetButton(button, true);
		} else {
			m_mouse.SetButton(button, false);
		}

		FlushMouseEvents();
	}

	void Input::MouseCursorEvent(int x, int y) {
		m_mouse.SetPosition(x, y);

		FlushCursorEvents();
	}

	void Input::FlushKeyboardEvents() const {
		for(int i=0; i < m_keyboardEventNames.size(); ++i) {
			m_eventManager.Run(m_keyboardEventNames[i]);
		}
	}
	void Input::FlushMouseEvents() const {
		for(int i=0; i < m_mouseEventNames.size(); ++i) {
			m_eventManager.Run(m_mouseEventNames[i]);
		}
	}
	void Input::FlushCursorEvents() const {
		for(int i=0; i < m_mouseCursorEventNames.size(); ++i) {
			m_eventManager.Run(m_mouseCursorEventNames[i]);
		}
	}
}