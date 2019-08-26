#include "nepch.h"

#include "NeonEngine.h"


namespace Neon {
	Application NeonEngine::s_Application;

	void NeonEngine::Init() {
		Debug::Logger::Init();
		NE_CORE_INFO("Neon Engine - Version 0.1");

		s_Application.Run();
	}
}
