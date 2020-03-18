#pragma once

#include "Core/Core.h"
#include "MacOS/MacOSWindow.h"

namespace Neon {
	/* Set the Window::Create function based on platform */
	#ifdef NE_PLATFORM_MACOS
		IWindow* IWindow::Create(const WindowSettings& settings) {
			return new MacOSWindow(settings);
		}
	#elif defined(NE_PLATFORM_WIN64)
		IWindow* IWindow::Create(const WindowSettings& settings) {
			return new MacOSWindow(settings);
		}
	#else
		#error "Current platform window type isn't supported"
	#endif
}
