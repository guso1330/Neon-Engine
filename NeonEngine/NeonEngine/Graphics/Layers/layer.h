 #pragma once

#include "nepch.h"

#include "Core/Time/Timer.h"

/*
	TODO:
	- Should the OnAttach, OnDetach, and OnUpdate be events that are emitted by the event system?
*/

namespace Neon {
	class Layer {
		public:
			Layer(const std::string& name = "Layer");
			virtual ~Layer() = default;

			/* Getters */
			inline const std::string& GetName() { return m_name; }

			/* Member (Virtual) functions */
			virtual void OnAttach() {}
			virtual void OnDetach() {}
			virtual void OnUpdate(Timestep ts) {}
			virtual void OnUpdateImGui(Timestep ts) {}

		private:
			std::string m_name;
	};
}
