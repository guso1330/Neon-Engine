#include "Core/Events/EventTypes.h"

namespace Neon {
	/* Window Events */
	WindowResizeEvent::WindowResizeEvent() {
		data = EventData(new WindowResizeEventData());
		dataSize = sizeof(data);
		type = NEON_EVENT_WINDOW_RESIZE;
	};

	/* Key Events */
	KeyEvent::KeyEvent() {
		data = EventData(new KeyPressEventData());
		dataSize = sizeof(data);
		type = "";
	}
	KeyPressEvent::KeyPressEvent() {
		type = NEON_EVENT_KEY_PRESS;
	};
	KeyDownEvent::KeyDownEvent() {
		type = NEON_EVENT_KEY_DOWN;
	}
	KeyReleaseEvent::KeyReleaseEvent() {
		type = NEON_EVENT_KEY_RELEASE;
	}
	KeyHoldEvent::KeyHoldEvent() {
		type = NEON_EVENT_KEY_HOLD;
	}

	/* Mouse Events */
	MouseEvent::MouseEvent() {
		data = EventData(new MouseEventData());
		dataSize = sizeof(data);
		type = "";
	}
	MousePressEvent::MousePressEvent() {
		type = NEON_EVENT_MOUSE_PRESS;
	}
	MouseDownEvent::MouseDownEvent() {
		type = NEON_EVENT_MOUSE_DOWN;
	}
	MouseReleaseEvent::MouseReleaseEvent() {
		type = NEON_EVENT_MOUSE_RELEASE;
	}
	MouseHoldEvent::MouseHoldEvent() {
		type = NEON_EVENT_MOUSE_HOLD;
	}

	/* Mouse Cursor Events */
	MouseCursorEvent::MouseCursorEvent() {
		data = EventData(new MouseCursorEventData());
		dataSize = sizeof(data);
		type = NEON_EVENT_MOUSE_CURSOR;
	}

	/* Mouse Scroll Events */
	MouseScrollEvent::MouseScrollEvent() {
		data = EventData(new MouseScrollEventData());
		dataSize = sizeof(data);
		type = NEON_EVENT_MOUSE_SCROLL;
	}
}
