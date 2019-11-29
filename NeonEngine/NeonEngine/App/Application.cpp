#include "App/Application.h"
#include "Graphics/Renderers/Renderer.h"

#include "nepch.h"

namespace Neon {
	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_Window(std::unique_ptr<IWindow>(IWindow::Create())),
		m_isRunning(false)
	{
		Init();
	}

	Application::Application(const WindowSettings &settings) :
		m_Window(std::unique_ptr<IWindow>(IWindow::Create(settings))),
		m_isRunning(false)
	{
		Init();
	}

	void Application::Init() {
		NE_CORE_INFO("Neon Engine - Version {}", NEON_ENGINE_VERSION);

		// Initialize Renderer
		Renderer::Init();

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

		m_Timer.Init();
		while (m_isRunning && !m_Window->isClosed()) {
			elapsed_time = m_Timer.GetElapsedTime();

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(elapsed_time);

			this->Update(elapsed_time);

			m_Window->Update();

			m_Timer.Tick();
		}
	}
}
