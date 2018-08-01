#pragma once

#include "./light.h"

#include <vector>
#include <glm/glm.hpp>
#include <iostream>

namespace neon {
	class AmbientLight : public Light {
		public:
			AmbientLight();
			~AmbientLight();

			void Bind(Renderable3d* renderable, Camera* camera);
			void Unbind();

		private:
			float m_intensity;
			glm::vec3 m_diffuse;
	};
}