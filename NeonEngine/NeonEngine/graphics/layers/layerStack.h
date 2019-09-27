#pragma once

#include "nepch.h"

#include "layer.h"

namespace Neon {
	class LayerStack {
		public:
			LayerStack();
			~LayerStack();

			void PushLayer(Layer* layer);
			void PushOverlay(Layer* overlay);
			void PopLayer(Layer* layer);
			void PopOverlay(Layer* overlay);

			std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
			std::vector<Layer*>::iterator end() { return m_Layers.end(); }
		private:
			std::vector<Layer*> m_Layers;
			unsigned int m_lastInsertIndex = 0;
	};
}
