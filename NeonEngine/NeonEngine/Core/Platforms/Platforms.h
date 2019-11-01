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
		#error "Windows x64 window isn't supported at this time"
	#else
		#error "Current platform window type isn't supported"
	#endif
}
