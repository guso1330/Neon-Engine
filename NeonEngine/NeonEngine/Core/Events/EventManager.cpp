#include "Core/Events/EventManager.h"
#include "Core/Events/EventTypes.h"

namespace Neon {
	void EventManager::InitCoreEvents() {
		AddEvent(NEON_EVENT_WINDOW_RESIZE, EventPtr(new WindowResizeEvent()));
		AddEvent(NEON_EVENT_KEY_PRESS, EventPtr(new KeyPressEvent()));
		AddEvent(NEON_EVENT_MOUSE_PRESS, EventPtr(new struct MousePressEvent()));
		AddEvent(NEON_EVENT_MOUSE_CURSOR, EventPtr(new struct MouseCursorEvent()));
	}

	bool EventManager::AddEvent(std::string name, EventPtr event) {
		if (s_eventStore.insert(std::make_pair(name, event)).second == true) {
			NE_CORE_INFO("EventManager: event {} was just created", name);
			return true;
		}

		return false;
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
