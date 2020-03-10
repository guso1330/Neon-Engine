#pragma once

#include "Graphics/Entities/renderable3d.h"
#include "Graphics/Cameras/Camera.h"

#include <vector>

namespace Neon {
	class Light {
		public:
			Light(){}

		protected:
			virtual ~Light() {}
			virtual void Bind(Renderable3d* renderable, Camera* camera) = 0;
			virtual void Unbind() = 0;

		protected:
			Program* m_program;
			std::vector<Shader*> m_shaders;
	};
}