#pragma once

#include "../core/platform/opengl/opengl.h"
#include "./eventManager.h"
#include "./eventTypes.h"
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
			/* Constructors & Destructors */
			Window(unsigned int width = 1280, unsigned int height = 720, bool fullscreen = false, const char* title = "");
			Window(const WindowSettings &settings);
			~Window();

			/* Getters */
			inline int GetWidth() const { return m_width; }
			inline int GetHeight() const { return m_height; }
			inline Input* GetInput() const { return m_Input.get(); }
			inline GLFWwindow* GetGLFWwindow() const { return m_Window; }
			inline GLFWwindow* GetCurrentWindow() const { return glfwGetCurrentContext(); }
			inline float GetTime() const { return glfwGetTime(); }

			/* Setters */
			void SetSize(unsigned int width, unsigned int height);
			void SetInputMode(int mode, int value);

			/* State Functions */
			inline bool isFullscreen() const { return m_fullscreen; }
			bool isClosed() const;

			/* Handler Functions */
			void Update();
			void Close();

		private:
			bool Init();
			void RunInit();
			void InitEvents();

		private:
			int m_width, m_height;
			bool m_fullscreen;
			
			const char* m_title;
			std::unique_ptr<Input> m_Input;
			GLFWwindow *m_Window;
	};
}
