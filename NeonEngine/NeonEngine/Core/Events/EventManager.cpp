#include "Core/Events/EventManager.h"
#include "Core/Events/EventTypes.h"

namespace Neon {
	void EventManager::InitCoreEvents() {
		AddEvent<WindowResizeEvent>(NEON_EVENT_WINDOW_RESIZE);
		AddEvent<KeyPressEvent>(NEON_EVENT_KEY_PRESS);
		AddEvent<KeyDownEvent>(NEON_EVENT_KEY_DOWN);
		AddEvent<KeyReleaseEvent>(NEON_EVENT_KEY_RELEASE);
		AddEvent<KeyHoldEvent>(NEON_EVENT_KEY_HOLD);
		AddEvent<MousePressEvent>(NEON_EVENT_MOUSE_PRESS);
		AddEvent<MouseDownEvent>(NEON_EVENT_MOUSE_DOWN);
		AddEvent<MouseReleaseEvent>(NEON_EVENT_MOUSE_RELEASE);
		AddEvent<MouseHoldEvent>(NEON_EVENT_MOUSE_HOLD);
		AddEvent<MouseCursorEvent>(NEON_EVENT_MOUSE_CURSOR);
		AddEvent<MouseScrollEvent>(NEON_EVENT_MOUSE_SCROLL);
	}

	void EventManager::PrintEvents() {
		unsigned short event_num = 0;
		NE_CORE_INFO("(PrintEvents) EventManager: contains {} events", s_eventStore.size());
		for(EventStore::iterator it = s_eventStore.begin(); it != s_eventStore.end(); ++it) {
			NE_CORE_INFO("(PrintEvents) EventManager: {}, event {}", (*it).first, event_num);
			++event_num;
		}
	}

	EventManager& EventManager::GetInstance() {
		static EventManager eventManager;

		if (!eventManager.s_initialized) {
			eventManager.InitCoreEvents();
		}

		eventManager.s_initialized = true;

		return eventManager;
	}
}
