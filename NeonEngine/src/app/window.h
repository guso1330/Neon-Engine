#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

namespace neon {
	class Window {
	public:
		Window(unsigned int width, unsigned int height, bool fullscreen, const char* title);
	private:
		int m_width, m_height;
		bool m_fullscreen;
		const char* m_title;
		GLFWwindow *m_window;
	private:
		bool init();
	};
}