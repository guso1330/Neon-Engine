#pragma once

#include "eventManager.h"

// TODO: Move event names to some macros

#define NEON_EVENT_WINDOW_RESIZE "WindowResize"
#define NEON_EVENT_KEY_PRESS "KeyPress"
#define NEON_EVENT_MOUSE_PRESS "MousePress"
#define NEON_EVENT_MOUSE_CURSOR "MouseCursor"

namespace Neon {
	
	/* Window Events */
	struct WindowResizeEventData : EventData {
		unsigned int width;
		unsigned int height;
	};

	struct WindowResizeEvent : Event {
		WindowResizeEvent() {
			std::shared_ptr<WindowResizeEventData> n_eventData(new WindowResizeEventData());
			type = NEON_EVENT_WINDOW_RESIZE;
			data = n_eventData;
			dataSize = sizeof(n_eventData);
		};
	};

	/* Input Events */
	struct KeyPressEventData : EventData {
		int button;
		int action;
		int mods;
	};

	struct KeyPressEvent : Event {
		KeyPressEvent() {
			std::shared_ptr<KeyPressEventData> n_eventData(new KeyPressEventData());
			type = NEON_EVENT_KEY_PRESS;
			data = n_eventData;
			dataSize = sizeof(n_eventData);
		};
	};

	struct MousePressEventData : EventData {
		int button;
		int action;
		int mods;
	};

	struct MousePressEvent : Event {
		MousePressEvent() {
			std::shared_ptr<MousePressEventData> n_eventData(new MousePressEventData());
			type = NEON_EVENT_MOUSE_PRESS;
			data = n_eventData;
			dataSize = sizeof(n_eventData);
		}
	};
	
	struct MouseCursorEventData : EventData {
		int x;
		int y;
	};

	struct MouseCursorEvent : Event {
		MouseCursorEvent() {
			std::shared_ptr<MouseCursorEventData> n_eventData(new MouseCursorEventData());
			type = NEON_EVENT_MOUSE_CURSOR;
			data = n_eventData;
			dataSize = sizeof(n_eventData);
		}
	};

 	/* typedef callback functions */
	typedef Callback<int, int> WindowResizeCallback;
	typedef Callback<int, int, int> KeyPressCallback;
	typedef Callback<int, int, int> MousePressCallback;
	typedef Callback<int, int> MouseCursorCallback;
}
