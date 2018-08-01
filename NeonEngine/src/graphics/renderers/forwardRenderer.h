#pragma once

#include "../entities/renderable3d.h"
#include "../entities/gameobject.h"
#include "../lights/ambientLight.h"

#include <vector>

namespace neon {
	class ForwardRenderer {
		public:
			ForwardRenderer();
			~ForwardRenderer();

			void Submit(Renderable3d* renderable);
			void Submit(GameObject* gameobject);

			inline void SetMainCamera(Camera* camera) { m_mainCamera = camera; }

			void SetUpDraw();
			void UnSetDraw();

			void Flush();

		private:
			// Data
			std::vector<Renderable3d*> m_renderables;
			AmbientLight* m_ambientLight;
			Camera* m_mainCamera;
	};
}