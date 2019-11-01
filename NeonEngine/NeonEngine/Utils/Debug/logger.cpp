#include "./logger.hpp"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Neon { namespace Debug {

	SPDLogger Logger::s_CoreLogger;
	SPDLogger Logger::s_ClientLogger;
	bool Logger::s_isInitialized = false;

	// Logger::Logger() {}

	// Logger::~Logger() {}

	SPDLogger& Logger::GetCoreLogger() {
		if (!s_isInitialized) {
			Init();
		}
		return s_CoreLogger;
	}
	SPDLogger& Logger::GetClientLogger() {
		if (!s_isInitialized) {
			Init();
		}
		return s_ClientLogger;
	}

	void Logger::Init() {
		s_CoreLogger = spdlog::stdout_color_mt("NEONENGINE");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
		
		s_isInitialized = true;
	}
}}