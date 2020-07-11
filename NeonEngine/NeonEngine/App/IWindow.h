#pragma once

#include "Core/Core.h"

#include "App/Input/Input.h"
#include "Core/Events/EventTypes.h"

namespace Neon {
	struct WindowSettings {
		bool fullscreen;
		std::string title;
		unsigned int height;
		unsigned int width;
		WindowSettings(
			const std::string& n_title = NEON_ENGINE_TITLE,
			unsigned int n_width = 1280,
			unsigned int n_height = 720,
			bool n_fullscreen = false
		) : 
			title(n_title),
			width(n_width),
			height(n_height),
			fullscreen(n_fullscreen)
		{}
	};

	class IWindow {
		public:
			IWindow() : m_Input(new Input) {}
			virtual ~IWindow() = default;

			virtual void Update() = 0;
			virtual void Close() = 0;

			/* Getters */
			virtual unsigned int GetWidth() const = 0;
			virtual unsigned int GetHeight() const = 0;
			virtual bool isFullscreen() const = 0;
			virtual bool isClosed() const = 0;
			virtual void* GetNativeWindow() const = 0;
			virtual inline Input* GetInput() const { return m_Input.get(); }

			/* Setters */
			virtual void SetSize(unsigned int width, unsigned int height) = 0;
			virtual void SetFullscreen(bool isFullscreen) = 0;
			virtual void SetVSync(bool enabled) = 0;
			virtual void SetTitle(const std::string& title) = 0;
			virtual void SetInputMode(int mode, int value) = 0;

			static IWindow* Create(const WindowSettings& settings = WindowSettings());

		protected:
			std::unique_ptr<Input> m_Input;
	};
}
