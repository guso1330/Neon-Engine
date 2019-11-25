#pragma once

#include "App/IWindow.h"
#include "App/timer.h"

#include "Utils/Debug/logger.hpp"

namespace Neon { namespace Debug {
	static double CalcFPS(IWindow* window = nullptr, double theTimeInterval = 1.0, std::string theWindowTitle = "NONE") {
		static Timer timer;
		// Static values which only get initialised the first time the function runs
		static double t0       = timer.GetTime(); // Set the initial time to now
		static int    fpsFrameCount = 0;             // Set the initial FPS frame count to 0
		static double fps           = 0.0;           // Set the initial FPS value to 0.0

		// Get the current time in seconds since the program started (non-static, so executed every time)
		double currentTime = timer.GetTime();

		// Ensure the time interval between FPS checks is sane (low cap = 0.1s, high-cap = 10.0s)
		// Negative numbers are invalid, 10 fps checks per second at most, 1 every 10 secs at least.
		if (theTimeInterval < 0.1)
		{
			theTimeInterval = 0.1;
		}
		if (theTimeInterval > 10.0)
		{
			theTimeInterval = 10.0;
		}

		// Calculate and display the FPS every specified time interval
		if ((currentTime - t0) > theTimeInterval)
		{
			// Calculate the FPS as the number of frames divided by the interval in seconds
			fps = (double)fpsFrameCount / (currentTime - t0);

			// If the user specified a window title to append the FPS value to...
			if (theWindowTitle != "NONE")
			{
				// Convert the fps value into a string using an output stringstream
				std::ostringstream stream;
				stream << fps;
				std::string fpsString = stream.str();

				// Append the FPS value to the window title details
				theWindowTitle += " | FPS: " + fpsString;

				// Convert the new window title to a c_str and set it
				std::string pszConstString = theWindowTitle;
				window->SetTitle(pszConstString);
			}
			else // If the user didn't specify a window to append the FPS to then output the FPS to the console
			{
				NE_CORE_WARN("FPS: {}", fps);
			}

			// Reset the FPS frame counter and set the initial time to be now
			fpsFrameCount = 0;
			t0 = timer.GetTime();
		}
		else // FPS calculation time interval hasn't elapsed yet? Simply increment the FPS frame counter
		{
			fpsFrameCount++;
		}

		// Return the current FPS - doesn't have to be used if you don't want it!
		return fps;
	}
}}