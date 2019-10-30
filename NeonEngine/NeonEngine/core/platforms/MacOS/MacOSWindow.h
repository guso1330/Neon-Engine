#pragma once

#include "App/IWindow.h"
#include "App/Input/input.h"
#include "App/eventManager.h"
#include "App/eventTypes.h"
#include "Core/Platforms/GLFW/GLFWContext.h"

namespace Neon {
	class MacOSWindow : public IWindow {
		public:
			MacOSWindow(const WindowSettings& settings);
			MacOSWindow(std::string title, unsigned int width, unsigned int height, bool fullscreen);
			~MacOSWindow();

			void Update() override;
			void Close() override;

			/* Getters */
			inline unsigned int GetWidth() const override { return m_width; }
			inline unsigned int GetHeight() const override { return m_height; }
			inline bool isFullscreen() const override { return m_isFullscreen; }
			bool isClosed() const override;
			inline void* GetNativeWindow() const override { return m_Window; };
			inline Input* GetInput() const { return m_Input.get(); }

			/* Setters */
			void SetSize(unsigned int width, unsigned int height) override;
			void SetFullscreen(bool isFullscreen) override;
			void SetVSync(bool enabled) override;
			void SetInputMode(int mode, int value);

		private:
			void RunInit();
			bool Init();
			void InitEvents();

		private:
			unsigned int m_width;
			unsigned int m_height;
			bool m_isFullscreen;
			bool m_vsyncEnabled;
			std::string m_title;

			GLFWwindow* m_Window;
			std::unique_ptr<Input> m_Input;
	};
}
