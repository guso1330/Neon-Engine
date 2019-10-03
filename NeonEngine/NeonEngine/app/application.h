#pragma once

#include "./window.h"
#include "./eventManager.h"
#include "./timer.h"
#include "../graphics/layers/layerStack.h"

namespace Neon {
	class Application {
		public:
			Application();
			Application(const WindowSettings &settings);
			virtual ~Application() = default;

			/* Getters */
			inline Window* GetWindow() { return m_Window.get(); }
			inline static Application& Get() { return *s_Instance; }

			/* Public Methods */
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);
			void Run();
			virtual void Update(Timestep ts) {}

		private:
			bool m_isRunning;
			std::unique_ptr<Window> m_Window;
			LayerStack m_LayerStack;
			Timer m_Timer;

		private:
			static Application* s_Instance;
	};

	Application* CreateApplication();
}
