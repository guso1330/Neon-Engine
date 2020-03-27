#pragma once

#include "Graphics/Layers/Layer.h"

namespace Neon {
	class ImGuiLayer : public Layer {
		public:
			/* Constructor & Destructor */
			ImGuiLayer();
			~ImGuiLayer();

			/* Public Methods */
			virtual void OnAttach();
			virtual void OnDetach();
			virtual void OnUpdate(Timestep ts);

		private:
			float m_Time = 0.0f;
	};
}
