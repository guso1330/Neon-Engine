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

	Timestep Timer::GetTime() const {
		return (Timestep)glfwGetTime();
	}

	Timestep Timer::GetElapsedTime() {
		m_currentTime = GetTime();
		return m_currentTime - m_lastTime;
	}

	void Timer::Tick() {
		m_lastTime = m_currentTime;
	}
}
