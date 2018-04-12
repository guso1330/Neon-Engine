#include "scene.h"

namespace neon {
	Scene::Scene() {}
	Scene::~Scene() {}

	void Scene::LoadSettings(const char *filename) {
		std::string settings = read_file(filename);
		std::cout << "Settings: " << settings << std::endl;
	}
}