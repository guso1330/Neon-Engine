namespace Neon {
	template<class E>
	bool EventManager::AddEvent(std::string name) {
		EventPtr event(new E());

		if (s_eventStore.insert(std::make_pair(name, event)).second == true) {
			NE_CORE_INFO("EventManager: event {} was just created", name);
			return true;
		}

		return false;
	}
	template<class C>
	std::pair<unsigned int, bool> EventManager::AddEventHandler(std::string eventName, const C &callback) {
		EventHandlerPtr n_eventHandlerPtr(new EventHandler());
		std::shared_ptr<std::vector<EventHandlerPtr> > n_eventHandlerVector(new std::vector<EventHandlerPtr>());
		EventStore::const_iterator eventIt;
		EventHandlerStore::iterator eventHandlerIt;

		eventIt = s_eventStore.find(eventName);
		eventHandlerIt = s_eventHandlerStore.find(eventName);

		// Search for event in s_eventStore to make sure it exists
		if (eventIt == s_eventStore.end()) {
			NE_CORE_WARN("EventManager: eventHandler couldn't be created since event {} doesn't exist", eventName);
			return std::make_pair(0, false);
		}

		// Set n_eventHandler variables
		n_eventHandlerPtr->id = ++s_handlerId;
		n_eventHandlerPtr->callback = BaseCallbackPtr(new C(callback));
		n_eventHandlerPtr->event = (*eventIt).second;

		// If eventhandler isn't found create new entry and insert it
		if (eventHandlerIt == s_eventHandlerStore.end()) {
			NE_CORE_INFO("EventManager: eventHandler {} was just created and added to eventHandlerStore under {}", n_eventHandlerPtr->id, eventName);
			n_eventHandlerVector->push_back(n_eventHandlerPtr);
			s_eventHandlerStore.insert(std::make_pair(
				eventName,
				(*n_eventHandlerVector)
			));
		} else {
			// Else insert new eventHandler into callback vector
			NE_CORE_INFO("EventManager: eventHandler {} was added to eventHandlerStore under {}", n_eventHandlerPtr->id, eventName);
			(*eventHandlerIt).second.push_back(n_eventHandlerPtr);
		}

		return std::make_pair(n_eventHandlerPtr->id, true);
	}

	template <class... ArgTypes>
	void EventManager::DispatchEvent(std::string name, ArgTypes... args) {
		typedef Callback<ArgTypes...> CallbackType;
		EventHandlerStore::const_iterator storeIt = s_eventHandlerStore.find(name);
		std::vector<EventHandlerPtr> callbackVector; // TODO: maybe store vector as pointer to ensure you're not copying the vector
		std::vector<EventHandlerPtr>::const_iterator it;

		if(storeIt != s_eventHandlerStore.end()) {
			callbackVector = storeIt->second;
			for (it = callbackVector.begin(); it != callbackVector.end(); ++it) {
				CallbackType* c = dynamic_cast<CallbackType*>((*it)->callback.get());
				if(c)
				{
					(*c)(args...);
				} else {
					NE_CORE_WARN("EventHandler {}: {} doesn't contain callback", (*it)->id, name);
				}
			}
		} else {
			// NE_CORE_WARN("EventManager: {} was not found and not run", name);
		}
	}
}
