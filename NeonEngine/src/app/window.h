#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace neon {
	class Window {
		public:
			Window(unsigned int width, unsigned int height, bool fullscreen, const char* title);
			~Window();
		private:
			int m_width, m_height;
			bool m_fullscreen;
			bool m_Closed;
			const char* m_title;
			GLFWwindow *m_window;
		private:
			bool Init();
		public:
			bool isClosed() const;
			void Clear() const;
			void Update();
			void SetClearColor(float r, float g, float b, float a);

			/* GETTERS */
			inline int GetWidth() const { return m_width; }
			inline int GetHeight() const { return m_height; }
	};
}
