#include "eventManager.h"

#include <map>
#include <vector>
#include <iterator>
#include <tuple>
#include <typeinfo>

namespace neon {
	typedef std::tuple<int, int, int> Click;
	typedef std::map<Click, const char*> ClickEvent;
	typedef std::map<const char*, std::vector<Click> > ClickEventMap;

	class InputDevice {
		public:
			InputDevice() {}
			virtual ~InputDevice() {}

			template<class T>
			bool BindEvent(const char *name, const T &callback) {
				return m_eventManager.Register(name, callback);
			}

			template<class... ArgTypes>
			void FireEvent(const char *name, ArgTypes... args) {
				m_eventManager.Run(name, args...);
			}

			template<class T>
			void BindClickEvent(const char *name, std::vector<Click> clickEvents, const T &callback) {
				// The event doesn't exist in ClickEventmap
				ClickEventMap::const_iterator it = m_clickEventMap.find(name);
				if(it == m_clickEventMap.end() && BindEvent(name, callback)) { // exists already so add clickEvents
					m_clickEventMap.insert(std::make_pair(name, clickEvents));
					for(int i=0; i < clickEvents.size(); ++i) {
						m_clickEvents.insert(std::make_pair(clickEvents[i], name));
					}
				}
			}

		protected:
			EventManager m_eventManager;
			ClickEvent m_clickEvents;
			ClickEventMap m_clickEventMap;
	};
}