#pragma once

#include "nepch.h"

#include "App/timer.h"

namespace Neon {
	class Layer {
		public:
			Layer(const std::string& name = "Layer");
			virtual ~Layer() = default;

			/* getters */
			inline const std::string& GetName() { return m_name; }

			virtual void OnAttach() {}
			virtual void OnDetach() {}
			virtual void OnUpdate(Timestep ts) {}

		private:
			std::string m_name;
	};
}
