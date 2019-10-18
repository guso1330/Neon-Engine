#pragma once

#include "nepch.h"
#include "../core/Core.h"

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

	class Window
	{
		public:
			virtual ~Window() = default;

			virtual void Update() = 0;
			virtual void Close() = 0;

			/* Getters */
			virtual unsigned int GetWidth() const = 0;
			virtual unsigned int GetHeight() const = 0;
			virtual bool isFullscreen() const = 0;
			virtual bool isClosed() const = 0;
			virtual void* GetNativeWindow() const = 0;

			/* Setters */
			virtual void SetSize(unsigned int width, unsigned int height) = 0;
			virtual void SetFullscreen(bool isFullscreen) = 0;
			virtual void SetVSync(bool enabled) = 0;

			static Window* Create(const WindowSettings& settings = WindowSettings());
	};
}