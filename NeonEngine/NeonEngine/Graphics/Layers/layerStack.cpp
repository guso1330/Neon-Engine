#include "layerStack.h"

namespace Neon {
	LayerStack::LayerStack() {}

	LayerStack::~LayerStack() {
		for (Layer* layer: m_Layers)
			delete layer;
	}

	void LayerStack::PushLayer(Layer* layer) {
		m_Layers.emplace(m_Layers.begin() + m_lastInsertIndex, layer);
		m_lastInsertIndex++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay) {
		m_Layers.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer) {
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin(), m_Layers.begin() + m_lastInsertIndex, layer);
		if (it != m_Layers.begin() + m_lastInsertIndex)
		{
			layer->OnDetach();
			m_Layers.erase(it);
			m_lastInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer* overlay) {
		std::vector<Layer*>::iterator it = std::find(m_Layers.begin() + m_lastInsertIndex, m_Layers.end(), overlay);
		if (it != m_Layers.end())
		{
			overlay->OnDetach();
			m_Layers.erase(it);
		}
	}
}
