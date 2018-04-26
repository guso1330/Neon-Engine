#include "eventManager.h"

namespace neon {
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

		private:
			EventManager m_eventManager;

	};
}