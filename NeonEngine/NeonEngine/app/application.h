#pragma once

#include "./window.h"
#include "./eventManager.h"

namespace Neon {
	class Application {
		public:
			Application();
			Application(const WindowSettings &settings);
			virtual ~Application() = default;
			// TODO: Think about whether the application needs a static instance of the opengl context, that way it can be passed around and used in different places (i.e. window.h)

			/* Getters */
			inline Window& GetWindow() { return *m_Window; }
			inline static Application& Get() { return *s_Instance; }

			/* Public Methods */
			void Run();

		private:
			bool m_isRunning;
			std::unique_ptr<EventManager> m_EventManager;
			std::unique_ptr<Window> m_Window;

		private:
			static Application* s_Instance;
			static OpenGLContext s_GLContext; // TODO: (TEMPORARY) remove the glContext and place that inside of the renderer
	};

	Application* CreateApplication();
}
