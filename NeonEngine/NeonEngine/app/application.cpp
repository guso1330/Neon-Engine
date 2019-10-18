#include "nepch.h"

#include "application.h"

namespace Neon {
	Application* Application::s_Instance = nullptr;

	Application::Application() {
		NE_CORE_INFO("Neon Engine - Version {}", NEON_ENGINE_VERSION);
		m_isRunning = false;

		m_Window = std::unique_ptr<Window>(Window::Create());
		s_Instance = this;
	}

	Application::Application(const WindowSettings &settings) {
		NE_CORE_INFO("Neon Engine - Version {}", NEON_ENGINE_VERSION);
		m_isRunning = false;

		m_Window = std::unique_ptr<Window>(Window::Create(settings));
		s_Instance = this;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void Application::Run() {
		Timestep elapsed_time = 0.0f;

		m_isRunning = true;

		EventManager::PrintEvents();
		m_Timer.Init();
		while (m_isRunning && !m_Window->isClosed()) {
			// Neon::Debug::Utils::calcFPS(m_Window->GetNativeWindow(), 1.0, "Neon Engine - Current FPS: ");
			elapsed_time = m_Timer.GetElapsedTime();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(elapsed_time);

			this->Update(elapsed_time);

			m_Window->Update();

			m_Timer.Tick();
		}
	}
}
