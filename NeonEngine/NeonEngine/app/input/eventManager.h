#pragma once

// TODO: Currently arguments are supported, but there is no way of actually 
// 		 passing new arguments or updating arguments.

#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <tuple>
#include <memory>

namespace neon {

	class BaseCallback {
		public:
			virtual ~BaseCallback() {}
	};

	template<class... ArgTypes>
	class Callback : public BaseCallback {
		typedef std::function<void(ArgTypes...)> Func;

		public:
			Func _f;

			Callback() {}
			Callback(Func f) { _f = f; }
			~Callback() {}

			void operator()(ArgTypes... args) { if(_f) _f(args...); }
	};

	class EventManager {
		typedef std::shared_ptr<BaseCallback> BaseCallbackPtr;
		typedef std::map<const char*, BaseCallbackPtr> EventsMap;

		public:
			EventManager() {}
			~EventManager() {}

			template<class T>
			bool Register(const char* name, const T &callback) {
				if(m_events.insert(std::make_pair(name, BaseCallbackPtr(new T(callback)))).second == true) {
					return true;
				} else {
					return false;
				}
			}

			// TODO: Understand this code haha
			template <class... ArgTypes>
			void Run(const char* name, ArgTypes... args) {
				typedef Callback<ArgTypes...> CallbackType;
				EventsMap::const_iterator it = m_events.find(name);
				
				if(it != m_events.end()) {
					CallbackType* c = dynamic_cast<CallbackType*>(it->second.get());
					if(c)
					{
						(*c)(args...);
					} else {
						std::cout << "EventManager: Callback function doesn't exist" << std::endl;
					}
				} else {
					std::cout << "EventManager: '" << name << "' was not found and run" << std::endl;
				}
			}

			// DEBUG FUNCTION
			void PrintAllEvents() {
				for(EventsMap::iterator it = m_events.begin(); it != m_events.end(); ++it) {
					std::cout << (*it).first << std::endl;
				}
			}

		private:
			// Todo: Should be static?
			EventsMap m_events;
	};
}