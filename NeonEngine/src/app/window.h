#pragma once

#include "../core/platform/opengl/opengl.h"
#include "./input/input.h"

#include <GLFW/glfw3.h>
#include <iostream>

namespace neon {
	class Window {
		public:
			Window(unsigned int width, unsigned int height, bool fullscreen, const char* title);
			~Window();

		public:
			bool isClosed() const;
			void SetInputMode(int mode, int value);
			void Update();

			/* GETTERS */
			inline int GetWidth() const { return m_width; }
			inline int GetHeight() const { return m_height; }
			inline bool isFullscreen() const { return m_fullscreen; }
			inline GLFWwindow* const GetGLFWwindow() const { return m_window; }
			inline GLFWwindow* const GetCurrentWindow() const { return glfwGetCurrentContext(); }
			inline Input* GetInput() const { return m_input; }

		private:
			bool Init();

		private:
			int m_width, m_height;
			bool m_fullscreen;
			
			const char* m_title;
			GLFWwindow *m_window;

		public:
			Input *m_input;
	};
}
