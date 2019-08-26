#pragma once

#include "./window.h"

namespace Neon {
	class Application {
		public:
			Application();
			~Application();
			// TODO: Think about whether the application needs a static instance of the opengl context, that way it can be passed around and used in different places (i.e. window.h)

			void Run();
		private:
			std::unique_ptr<Window> m_Window;
	};
}