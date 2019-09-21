#include "nepch.h"

#include "application.h"

namespace Neon {
	Application* Application::s_Instance = nullptr;
	OpenGLContext Application::s_GLContext;

	Application::Application() :
		m_EventManager(new EventManager()),
		m_Window(new Window())
	{
		NE_CORE_INFO("Neon Engine - Version {}", NEON_ENGINE_VERSION);
		m_isRunning = false;

		s_Instance = this;
		s_GLContext.CreateContext();
	}

	Application::Application(const WindowSettings &settings) :
		m_EventManager(new EventManager()),
		m_Window(new Window(settings))
	{
		NE_CORE_INFO("Neon Engine - Version {}", NEON_ENGINE_VERSION);
		m_isRunning = false;

		s_Instance = this;
		s_GLContext.CreateContext();
	}

	void Application::Run() {
		float elasped_time = 0,
			  last_time = m_Window->GetTime(),
			  current_time = 0;

		m_isRunning = true;

		m_EventManager->PrintEvents();
		
		while (m_isRunning && !m_Window->isClosed()) {
			Neon::Debug::Utils::calcFPS(m_Window->GetGLFWwindow(), 1.0, "Neon Engine - Current FPS: ");

			// TODO: remove this from the application and abstract out the Rendering platform
			s_GLContext.Clear();

			/*
				Update timer
				- TODO: extract this to it's own class and handle different types of update loops
			*/
			current_time = glfwGetTime();
			elasped_time = current_time - last_time;

			m_Window->Update();

			last_time = current_time;
		}
	}
}
