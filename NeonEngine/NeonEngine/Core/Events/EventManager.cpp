#include "Core/Events/EventManager.h"

namespace Neon {
	EventStore EventManager::s_eventStore;
	EventHandlerStore EventManager::s_eventHandlerStore;
	unsigned int EventManager::s_handlerId = 0;

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
}
