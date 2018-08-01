#pragma once

#include "./scene.h"
#include "./window.h"

#include <vector>

namespace neon {
	class Application {
		public:
			Application();
			~Application();

			inline const std::vector<Scene*> &GetScene() const { return m_scenes; };

			void Add(Scene* n_scene);
			
			// void Load(Scene* n_scene);

		private:
			std::vector<Scene*> m_scenes;
	};
}