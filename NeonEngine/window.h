#pragma once
#include "GLFW\glfw3.h"
#include <string>

namespace neon {
	class Window {
		private:
			unsigned int m_Width,
				m_Height;
			std::string m_Name;
		public:
			Window() {}
			Window(const unsigned int width, const unsigned height, const std::string& name);

			void InitWindow();
	};
}