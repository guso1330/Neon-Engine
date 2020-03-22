#pragma once

/*
	TODO:
	 - Currently arguments are supported, but there is no way of actually passing new arguments or updating arguments.
	 - Expose some global macro functions to access the event manager
	 - Implement Subscribe and Unsubscribe
	 - Event bubbling
	 - Make class a singleton?
*/
#include "Core/Types/Singleton.h"
#include "Core/Types/Callback.h"
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

	class EventManager : public Singleton {
		public:
			/* Constructors and destructors */
			~EventManager() = default;
		private:
			void InitCoreEvents();
		public:
			/* Public Member Functions */
			bool AddEvent(std::string name, EventPtr event);
			template<class T>
			std::pair<unsigned int, bool> AddEventHandler(std::string eventName, const T &callback);
			template <class... ArgTypes>
			void DispatchEvent(std::string name, ArgTypes... args);

			// bool RemoveEvent(string name);
			// bool RemoveEventHandler(string name, uint id);
			// const Event Subscribe(string name);
			// bool Unsubscribe(string name);
			// bool DispatchEventHandler(string name, uint id, Args ...);

			/* Debug function */
			void PrintEvents();

			/* Getters */
			static EventManager& GetInstance();
		private:
			bool s_initialized = false;
			unsigned int s_handlerId = 0;
			EventStore s_eventStore;
			EventHandlerStore s_eventHandlerStore;
	};
}

#include "Core/Events/EventManager.tpp"
