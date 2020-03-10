#include "App/Input/Mouse.h"

namespace Neon {
	Mouse::Mouse() {
		for(int i=0; i < MAX_BUTTONS; ++i) {
			m_buttons[i] = false;
		}
		m_pos = glm::vec2(0.0f);
	}

	Mouse::~Mouse() {}
}