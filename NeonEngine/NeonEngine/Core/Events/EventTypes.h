#pragma once

#include "Core/Events/EventManager.h"

// TODO: Move event names to some macros
#define NEON_EVENT_WINDOW_RESIZE "Neon::WindowResize"
#define NEON_EVENT_KEY_PRESS     "Neon::KeyPress"
#define NEON_EVENT_KEY_DOWN      "Neon::KeyDown"
#define NEON_EVENT_KEY_RELEASE   "Neon::KeyRelease"
#define NEON_EVENT_KEY_HOLD      "Neon::KeyHold"
#define NEON_EVENT_MOUSE_PRESS   "Neon::MousePress"
#define NEON_EVENT_MOUSE_DOWN    "Neon::MouseDown"
#define NEON_EVENT_MOUSE_RELEASE "Neon::MouseRelease"
#define NEON_EVENT_MOUSE_HOLD    "Neon::MouseHold"
#define NEON_EVENT_MOUSE_CURSOR  "Neon::MouseCursor"
#define NEON_EVENT_MOUSE_SCROLL  "NEON::MouseScroll"

namespace Neon {
	
	/* Window Events */
	struct WindowResizeEventData {
		unsigned int width;
		unsigned int height;
	};
	struct WindowResizeEvent : Event {
		WindowResizeEvent();
	};

	/* Key Events */
	struct KeyPressEventData {
		int button;
		int scancode;
		int action;
		int mods;
	};
	struct KeyEvent : Event {
		KeyEvent();
	};
	struct KeyPressEvent : KeyEvent {
		KeyPressEvent();
	};
	struct KeyDownEvent : KeyEvent {
		KeyDownEvent();
	};
	struct KeyReleaseEvent : KeyEvent {
		KeyReleaseEvent();
	};
	struct KeyHoldEvent : KeyEvent {
		KeyHoldEvent();
	};

	/* Mouse Events */
	struct MouseEventData {
		int button;
		int action;
		int mods;
	};
	struct MouseEvent : Event {
		MouseEvent();
	};
	struct MousePressEvent : MouseEvent {
		MousePressEvent();
	};
	struct MouseDownEvent : MouseEvent {
		MouseDownEvent();
	};
	struct MouseReleaseEvent : MouseEvent {
		MouseReleaseEvent();
	};
	struct MouseHoldEvent : MouseEvent {
		MouseHoldEvent();
	};

	/* Mouse Cursor Events */
	struct MouseCursorEventData {
		double x;
		double y;
	};
	struct MouseCursorEvent : Event {
		MouseCursorEvent();
	};

	/* Mouse Scroll Events */
	struct MouseScrollEventData {
		double xOffset;
		double yOffset;
	};
	struct MouseScrollEvent : Event {
		MouseScrollEvent();
	};

	/* typedef callback functions */
	typedef Callback<Event&> EventCallback;
	typedef Callback<int, int> WindowResizeCallback;
	typedef Callback<int, int, int, int> KeyPressCallback;
	typedef Callback<int, int, int> MousePressCallback;
	typedef Callback<double, double> MouseCursorCallback;
	typedef Callback<double, double> MouseScrollCallback;
}
