#pragma once

#include "EventSystem/Types.h"

// TODO: Move event names to some macros
#define NEON_WINDOW_RESIZE_EVENT "Neon::WindowResize"
#define NEON_KEY_PRESS_EVENT     "Neon::KeyPress"
#define NEON_KEY_DOWN_EVENT      "Neon::KeyDown"
#define NEON_KEY_RELEASE_EVENT   "Neon::KeyRelease"
#define NEON_KEY_HOLD_EVENT      "Neon::KeyHold"
#define NEON_MOUSE_PRESS_EVENT   "Neon::MousePress"
#define NEON_MOUSE_DOWN_EVENT    "Neon::MouseDown"
#define NEON_MOUSE_RELEASE_EVENT "Neon::MouseRelease"
#define NEON_MOUSE_HOLD_EVENT    "Neon::MouseHold"
#define NEON_MOUSE_CURSOR_EVENT  "Neon::MouseCursor"
#define NEON_MOUSE_SCROLL_EVENT  "Neon::MouseScroll"

namespace Neon {
	
	/* Window Events */
	struct WindowResizeEvent : public EventSystem::Event {
		unsigned int width;
		unsigned int height;
	};

	/* Key Events */
	struct KeyPressEvent : public EventSystem::Event {
		int key;
		int scancode;
		int action;
		int mods;
	};

	/* Mouse Events */
	struct MousePressEvent : public EventSystem::Event {
		int button;
		int action;
		int mods;
	};

	/* Mouse Cursor Events */
	struct MouseCursorEvent : public EventSystem::Event {
		double x;
		double y;
	};

	/* Mouse Scroll Events */
	struct MouseScrollEvent : public EventSystem::Event {
		double xOffset;
		double yOffset;
	};
}
