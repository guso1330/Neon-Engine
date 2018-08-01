#include "./app.h"

namespace neon {
	Application::Application() {}

	Application::~Application() {}

	void Application::Add(Scene* n_scene) {
		m_scenes.push_back(n_scene);
	}
}