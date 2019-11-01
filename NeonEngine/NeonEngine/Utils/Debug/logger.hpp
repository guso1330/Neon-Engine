#pragma once

/*
	Logging:
	- Logger class functionality
		1. 2 generic console loggers. One for the NeonEngine and another for the client application
			- These loggers will log directly to the console, which will allow for easier debugging
			- These loggers will be global and accessible from anywhere using macro functions
		2. Instantiate other loggers that can be used in subsystem
			- Loggers can either be console loggers or logged directly to a file

	- TODO
		- Allow for instanced versions of the logger system, that can be outputted to log files
*/
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Neon { namespace Debug {

	typedef std::shared_ptr<spdlog::logger> SPDLogger;

	class Logger {
		public:
			// Logger();
			// ~Logger();

			static void Init();

			static SPDLogger& GetCoreLogger();
			static SPDLogger& GetClientLogger();

		private:
			static SPDLogger s_CoreLogger;
			static SPDLogger s_ClientLogger;

			// std::vector<SPDLogger> m_Loggers;
			static bool s_isInitialized;
	};
}}

// Core log macros
#define NE_CORE_TRACE(...)    ::Neon::Debug::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define NE_CORE_INFO(...)     ::Neon::Debug::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define NE_CORE_WARN(...)     ::Neon::Debug::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define NE_CORE_ERROR(...)    ::Neon::Debug::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define NE_CORE_CRITICAL(...) ::Neon::Debug::Logger::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define NE_TRACE(...)         ::Neon::Debug::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define NE_INFO(...)          ::Neon::Debug::Logger::GetClientLogger()->info(__VA_ARGS__)
#define NE_WARN(...)          ::Neon::Debug::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define NE_ERROR(...)         ::Neon::Debug::Logger::GetClientLogger()->error(__VA_ARGS__)
#define NE_CRITICAL(...)      ::Neon::Debug::Logger::GetClientLogger()->critical(__VA_ARGS__)
