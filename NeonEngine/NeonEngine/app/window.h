#pragma once

#include "../core/platform/opengl/opengl.h"
#include "./input/input.h"

#include <GLFW/glfw3.h>

namespace Neon {
	struct WindowSettings {
		unsigned int width = 1280;
		unsigned int height = 720;
		bool fullscreen = false;
		const char* title = "";
	};

	class Window {
		public:
			Window(unsigned int width = 1280, unsigned int height = 720, bool fullscreen = false, const char* title = "");
			Window(const WindowSettings &settings);
			~Window();

			/* GETTERS */
			inline int GetWidth() const { return m_width; }
			inline int GetHeight() const { return m_height; }
			inline bool isFullscreen() const { return m_fullscreen; }
			inline GLFWwindow* const GetGLFWwindow() const { return m_window; }
			inline GLFWwindow* const GetCurrentWindow() const { return glfwGetCurrentContext(); }
			inline Input* GetInput() const { return m_input; }
			inline float GetTime() const { return glfwGetTime(); }

			/* SETTERS */
			void SetSize(unsigned int width, unsigned int height);
			void SetInputMode(int mode, int value);

			bool isClosed() const;
			void Update();

		private:
			bool Init();
			void RunInit();

		private:
			int m_width, m_height;
			bool m_fullscreen;
			
			const char* m_title;
			GLFWwindow *m_window;
			Input *m_input; // should be static?
	};
}
