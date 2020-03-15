#pragma once

#include "Core/Time/Timer.h"
#include "Core/ECS/ECSManager.h"
#include "Core/Events/EventManager.h"
#include "Graphics/Layers/layerStack.h"
#include "App/IWindow.h"

/*
	TODO:
	- Support post construction initialization
	- Ensure application class follows the singleton pattern 100%
	- Rethink layers and overlays place inside Application
*/

namespace Neon {

	using namespace ECS;

	class Application {
		public:
			Application();
			Application(const WindowSettings &settings);
			virtual ~Application() = default;

			/* Getters */
			inline IWindow* GetWindow() { return m_pWindow.get(); }
			inline static Application& Get() { return *s_Instance; }

			/* Public Methods */
			virtual bool Init() = 0;
			void Run();
			virtual void Update(Timestep ts) = 0;
			// Layer Functions
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);

		private:
			void Initialize();

		private:
			bool m_initialized;
			bool m_isRunning;
			Timer m_Timer;
			std::unique_ptr<IWindow> m_pWindow;
			LayerStack m_LayerStack;

		private:
			static Application* s_Instance;
	};

	Application* CreateApplication();
}
