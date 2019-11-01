#pragma once

#define MAX_BUTTONS 32

#include <glm/glm.hpp>

#include <iostream>
#include <string>
#include <algorithm>

namespace Neon {

	enum ButtonEvents {
		NEON_BUTTON_UP,
		NEON_BUTTON_DOWN,
		NEON_BUTTON_HOLD,
		NEON_MOUSE_SCROLL,
		NEON_MOUSE_MOVE
	};

	class Mouse {
		public:
			Mouse();
			~Mouse();

			inline void SetButton(const int button, const bool state) { m_buttons[button] = state; }
			inline void SetPosition(int x, int y) { m_pos.x = x; m_pos.y = y; }

			inline const bool GetButton(const int button) const { return m_buttons[button]; }
			inline const glm::vec2 &GetPosition() const { return m_pos; }

		private:
			bool m_buttons[MAX_BUTTONS];
			glm::vec2 m_pos;
	};
}