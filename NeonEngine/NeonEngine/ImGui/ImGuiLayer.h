#pragma once

#include "Core/Events/EventTypes.h"
#include "Graphics/Layers/Layer.h"

namespace Neon {
	class ImGuiLayer : public Layer {
		public:
			/* Constructor & Destructor */
			ImGuiLayer();
			~ImGuiLayer() = default;

			/* Public Methods */
			void Begin();
			void End();
			virtual void OnAttach() override;
			virtual void OnDetach() override;
	};
}
