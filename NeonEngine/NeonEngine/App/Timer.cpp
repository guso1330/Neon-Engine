#include "Timer.h"

#include "Core/Core.h"

namespace Neon {
	#ifdef NE_PLATFORM_MACOS
		TimerAPI Timer::API = TimerAPI::GLFW;
	#else
		TimerAPI Timer::API = TimerAPI::NONE;
	#endif

	Timer::Timer() {
		m_currentTime = 0.0f;
		m_lastTime = 0.0f;
	}

	Timer::~Timer() {}

	void Timer::Init() {
		switch(GetAPI()) {
			case TimerAPI::GLFW:
				m_lastTime = glfwGetTime();
				break;
			default:
				NE_CORE_ASSERT(false, "Timer: Failed to establish API");
				break;
		}
	}

	const Timestep Timer::GetTime() const {
		switch(GetAPI()) {
			case TimerAPI::GLFW:
				return (Timestep)glfwGetTime();
			default:
				NE_CORE_ASSERT(false, "Timer: Failed to establish API");
				return 0;
		}
	}

	const Timestep Timer::GetElapsedTime() {
		m_currentTime = GetTime();
		return m_currentTime - m_lastTime;
	}

	void Timer::Tick() {
		m_lastTime = m_currentTime;
	}
}
