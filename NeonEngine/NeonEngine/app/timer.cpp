#include "timer.h"

namespace Neon {
	Timer::Timer() {
		m_currentTime = 0.0f;
		m_lastTime = 0.0f;
	}

	Timer::~Timer() {}

	void Timer::Init() {
		m_lastTime = glfwGetTime();
	}

	Timestep Timer::GetCurrentTime() {
		m_currentTime = glfwGetTime();
		return m_currentTime;
	}

	Timestep Timer::GetElapsedTime() {
		return GetCurrentTime() - m_lastTime;
	}

	void Timer::Tick() {
		m_lastTime = m_currentTime;
	}
}
