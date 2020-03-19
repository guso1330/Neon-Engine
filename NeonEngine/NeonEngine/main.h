#pragma once

extern Neon::Application* Neon::CreateApplication();

int main(int argc, char const *argv[]) {
	Neon::Debug::Logger::Init();

	auto app = Neon::CreateApplication();
	NE_CORE_ASSERT(app->Init(), "Application Init(): Failed to initialize application");
	app->Run();
	delete app;

	/* code */
	return EXIT_SUCCESS;
}
