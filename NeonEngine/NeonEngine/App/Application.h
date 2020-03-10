#pragma once

#include "Core/Time/Timer.h"
#include "Core/ECS/EntityManager.h"
#include "Core/Events/EventManager.h"
#include "Graphics/Layers/layerStack.h"
#include "App/IWindow.h"

/*
	TODO:
	- Ensure application class follows the singleton pattern 100%
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
			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);
			void Run();
			virtual void Update(Timestep ts) {}

		private:
			void Init();

		private:
			bool m_isRunning;
			Timer m_Timer;
			std::unique_ptr<IWindow> m_pWindow;
			LayerStack m_LayerStack;
			EntityManager m_EntityManager;

		private:
			static Application* s_Instance;
	};

	Application* CreateApplication();
}
