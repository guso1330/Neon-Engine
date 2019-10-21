#pragma once

/*
	TODO:
	 - Currently arguments are supported, but there is no way of actually passing new arguments or updating arguments.
	 - Expose some global macro functions to access the event manager
	 - Implement Subscribe and Unsubscribe
	 - Event bubbling
*/
#include "../core/Types/Callback.h"
#include "nepch.h"

namespace Neon {

	struct EventData {};

	struct Event {
		std::string type;
		std::shared_ptr<EventData> data;
		size_t dataSize; // Size in bytes [e.g sizeof(SomeEventData)]
	};

	struct EventHandler {
		unsigned int id; // TODO: This should be private
		std::shared_ptr<Event> event; // TODO: this is probably not needed
		std::shared_ptr<BaseCallback> callback;
	};

	typedef std::shared_ptr<BaseCallback> BaseCallbackPtr;
	typedef std::shared_ptr<Event> EventPtr;
	typedef std::shared_ptr<EventHandler> EventHandlerPtr;
	typedef std::unordered_map<std::string, EventPtr> EventStore;
	typedef std::unordered_map<std::string, std::vector<EventHandlerPtr> > EventHandlerStore;

	class EventManager {
		public:
			/* Constructors and destructors */
			EventManager() = default;

			~EventManager() = default;

			/* Public Member Functions */
			static bool AddEvent(std::string name, EventPtr event);

			template<class T>
			static std::pair<unsigned int, bool> AddEventHandler(std::string eventName, const T &callback) {
				EventHandlerPtr n_eventHandlerPtr(new EventHandler());
				std::shared_ptr<std::vector<EventHandlerPtr> > n_eventHandlerVector(new std::vector<EventHandlerPtr>());
				EventStore::const_iterator eventIt = s_eventStore.find(eventName);
				EventHandlerStore::iterator eventHandlerIt = s_eventHandlerStore.find(eventName);

				// Search for event in s_eventStore to make sure it exists
				if (eventIt == s_eventStore.end()) {
					NE_CORE_WARN("EventManager: eventHandler couldn't be created since event {} doesn't exist", eventName);
					return std::make_pair(0, false);
				}

				// Set n_eventHandler variables
				n_eventHandlerPtr->id = ++s_handlerId;
				n_eventHandlerPtr->callback = BaseCallbackPtr(new T(callback));
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

			// bool RemoveEvent(string name);
			// bool RemoveEventHandler(string name, uint id);
			// const Event Subscribe(string name);
			// bool Unsubscribe(string name);

			template <class... ArgTypes>
			static void DispatchEvent(std::string name, ArgTypes... args) {
				typedef Callback<ArgTypes...> CallbackType;
				EventHandlerStore::const_iterator storeIt = s_eventHandlerStore.find(name);
				std::vector<EventHandlerPtr> callbackVector; // TODO: maybe store vector as pointer to ensure you're not copying the vector
				std::vector<EventHandlerPtr>::const_iterator vecIt;

				if(storeIt != s_eventHandlerStore.end()) {
					callbackVector = storeIt->second;
					for (vecIt = callbackVector.begin(); vecIt != callbackVector.end(); ++vecIt) {
						CallbackType* c = dynamic_cast<CallbackType*>((*vecIt)->callback.get());
						if(c)
						{
							(*c)(args...);
						} else {
							NE_CORE_WARN("EventHandler {}: {} doesn't contain callback", (*vecIt)->id, name);
						}
					}
				} else {
					NE_CORE_WARN("EventManager: {} was not found and not run", name);
				}
			}

			// bool DispatchEventHandler(string name, uint id, Args ...);

			/* Debug function */
			static void PrintEvents();

		private:
			static EventStore s_eventStore;
			static EventHandlerStore s_eventHandlerStore;
			static unsigned int s_handlerId;
	};
}
