#include "nepch.h"

#include "EventSystem/EventSystem.h"
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
			KeyPressEvent event = EventSystem::EventManager::GetInstance().CreateEvent<KeyPressEvent>();

			event.key = (int)key;
			event.scancode = (int)scancode;
			event.action = (int)action;
			event.mods = (int)mods;

			EventSystem::EventManager::GetInstance().DispatchEvent(type, (const KeyPressEvent&)event);
		};

		if(action != NEON_KEY_UP) {
			m_Keyboard.SetKey(key, true);
			callEventManagerFn(NEON_KEY_DOWN_EVENT);
		} else if (action == NEON_KEY_HOLD) {
			// TODO: Get key hold to work
			m_Keyboard.SetKey(key, true);
			callEventManagerFn(NEON_KEY_HOLD_EVENT);
		} else {
			m_Keyboard.SetKey(key, false);
			callEventManagerFn(NEON_KEY_RELEASE_EVENT);
		}

		callEventManagerFn(NEON_KEY_PRESS_EVENT);

		s_Timer.Tick();
	}

	void Input::MousePressEvent(const int button, const int action, const int mods) {
		std::function<void(std::string)> callEventManagerFn = [button, action, mods](std::string type) {
			struct MousePressEvent event = EventSystem::EventManager::GetInstance().CreateEvent<struct MousePressEvent>();

			event.button = (int)button;
			event.action = (int)action;
			event.mods = (int)mods;

			EventSystem::EventManager::GetInstance().DispatchEvent(type, (const struct MousePressEvent&)event);
		};

		if(action != NEON_BUTTON_UP) {
			m_Mouse.SetButton(button, true);
			callEventManagerFn(NEON_MOUSE_DOWN_EVENT);
		} else {
			m_Mouse.SetButton(button, false);
			callEventManagerFn(NEON_MOUSE_RELEASE_EVENT);
		}
		// TODO: Add mouse hold

		callEventManagerFn(NEON_MOUSE_PRESS_EVENT);

		s_Timer.Tick();
	}

	void Input::MouseCursorEvent(const double x, const double y) {
		struct MouseCursorEvent event = EventSystem::EventManager::GetInstance().CreateEvent<struct MouseCursorEvent>();

		event.x = (double)x;
		event.y = (double)y;

		m_Mouse.SetPosition(x, y);

		EventSystem::EventManager::GetInstance().DispatchEvent(NEON_MOUSE_CURSOR_EVENT, (const struct MouseCursorEvent&)event);

		s_Timer.Tick();
	}

	void Input::MouseScrollEvent(const double xOffset, const double yOffset) {
		struct MouseScrollEvent event = EventSystem::EventManager::GetInstance().CreateEvent<struct MouseScrollEvent>();

		event.xOffset = (double)xOffset;
		event.yOffset = (double)yOffset;

		EventSystem::EventManager::GetInstance().DispatchEvent(NEON_MOUSE_SCROLL_EVENT, (const struct MouseScrollEvent&)event);

		s_Timer.Tick();
	}
}
