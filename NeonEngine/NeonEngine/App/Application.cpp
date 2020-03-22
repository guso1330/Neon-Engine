#include "App/Application.h"
#include "Graphics/Renderers/Renderer.h"
#include "Core/Platforms/Platforms.h"

#include "nepch.h"

namespace Neon {
	Application* Application::s_Instance = nullptr;

	Application::Application() :
		m_pWindow(std::unique_ptr<IWindow>(IWindow::Create())),
		m_isRunning(false),
		m_initialized(false)
	{
		Initialize();
	}

	Application::Application(const WindowSettings &settings) :
		m_pWindow(std::unique_ptr<IWindow>(IWindow::Create(settings))),
		m_isRunning(false),
		m_initialized(false)
	{
		Initialize();
	}

	void Application::Initialize() {
		NE_CORE_INFO("Neon Engine - Version {}", NEON_ENGINE_VERSION);

		// Initialize Subsystems
		std::function<bool()> initializeSubSystemsFn = [this]() {
			return Renderer::GetInstance().Init() && ECSManager::GetInstance().Init();
		};

		if (!m_initialized &&
			initializeSubSystemsFn()) {
			m_initialized = true;
			s_Instance = this;
		}
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
		while (m_isRunning && !m_pWindow->isClosed()) {
			elapsed_time = m_Timer.GetElapsedTime();

			// Clear Renderer
			Renderer::GetInstance().Clear();

			// Update ECS Systems
			ECSManager::GetInstance().Update(elapsed_time);

			// Update layers
			for (Layer* layer : m_LayerStack)
				layer->OnUpdate(elapsed_time);

			// Update application
			Update(elapsed_time);

			// Update window
			m_pWindow->Update();

			Renderer::GetInstance().Flush();

			m_Timer.Tick();
		}
	}
}
