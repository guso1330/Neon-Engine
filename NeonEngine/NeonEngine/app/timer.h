#pragma once

#include <GLFW/glfw3.h>

namespace Neon {

	class Timestep
	{
		public:
			Timestep(float time = 0.0f)
				: m_Time(time)
			{}

			operator float() const { return m_Time; }

			float GetSeconds() const { return m_Time; }
			float GetMilliseconds() const { return m_Time * 1000.0f; }
		private:
			float m_Time;
	};

	class Timer {
		public:
			Timer();
			~Timer();

			void Init();

			Timestep GetCurrentTime();
			Timestep GetElapsedTime();

			void Tick();
		private:
			Timestep m_currentTime;
			Timestep m_lastTime;
	};
}
