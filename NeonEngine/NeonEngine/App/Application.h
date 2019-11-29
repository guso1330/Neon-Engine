#pragma once

#include "App/IWindow.h"
#include "Core/Platforms/Platforms.h"
#include "App/eventManager.h"
#include "App/Timer.h"
#include "Graphics/Layers/layerStack.h"

namespace Neon {
	class Application {
		public:
			Application();
			Application(const WindowSettings &settings);
			virtual ~Application() = default;

			/* Getters */
			inline IWindow* GetWindow() { return m_Window.get(); }
			inline static Application& Get() { return *s_Instance; }

			/* Public Methods */
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);
			void Run();
			virtual void Update(Timestep ts) {}

		private:
			void Init();

		private:
			bool m_isRunning;
			std::unique_ptr<IWindow> m_Window;
			LayerStack m_LayerStack;
			Timer m_Timer;

		private:
			static Application* s_Instance;
	};

	Application* CreateApplication();
}
