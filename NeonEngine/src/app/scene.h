#pragma once

#include "../graphics/cameras/camera.h"
#include "../utils/file_utils/fileUtils.h"

#include <string>
#include <vector>

namespace neon {
	class Scene {
		public:
			Scene();
			~Scene();

			void LoadSettings(const char *filename);

		private:
			std::vector<Camera*> m_cameras;
			std::string settings;
	};
}