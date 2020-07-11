#pragma once

#include "Core/Platforms/GLFW/GLFWContext.h"
#include "App/IWindow.h"

namespace Neon {
	class MacOSWindow : public IWindow {
		public:
			MacOSWindow(const WindowSettings& settings);
			MacOSWindow(std::string title, unsigned int width, unsigned int height, bool fullscreen);
			~MacOSWindow();

		private:
			void RunInit();
			bool Init();
			void InitEvents();

		public:
			/* Public Methods */
			void Update() override;
			void Close() override;

			/* Getters */
			inline unsigned int GetWidth() const override { return m_width; }
			inline unsigned int GetHeight() const override { return m_height; }
			inline bool isFullscreen() const override { return m_isFullscreen; }
			bool isClosed() const override;
			inline void* GetNativeWindow() const override { return m_Window; };

			/* Setters */
			void SetSize(unsigned int width, unsigned int height) override;
			void SetFullscreen(bool isFullscreen) override;
			void SetVSync(bool enabled) override;
			void SetTitle(const std::string& title) override;
			void SetInputMode(int mode, int value) override;

		private:
			unsigned int m_width;
			unsigned int m_height;
			bool m_isFullscreen;
			bool m_vsyncEnabled;
			std::string m_title;

			GLFWwindow* m_Window;
	};
}
