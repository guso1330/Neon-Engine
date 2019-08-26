#pragma once

/* Utils */
#include "utils/debug/logger.hpp"
#include "utils/debug/debug.h"
#include "utils/fileUtils/fileUtils.h"

/* Core */
#include "core/platform/opengl/opengl.h"
#include "core/ecs/ecs.h"

/* Graphics */
#include "graphics/cameras/camera.h"
#include "graphics/entities/vertex.h"
#include "graphics/entities/transform.h"
#include "graphics/entities/renderable3d.h"
#include "graphics/entities/renderableCollection.h"
// light includes, not used yet

/* Shaders */
#include "shaders/material.h"

/* App */
#include "app/application.h"
#include "app/input/input.h"

namespace Neon {
	class NeonEngine {
		public:
			static void Init();
		private:
			static Application s_Application;
	};
}
