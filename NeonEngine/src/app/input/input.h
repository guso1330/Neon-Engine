#pragma once

#include "keyboard.h"
#include "mouse.h"

namespace neon {
	class Input {
		public:
			Input();
			~Input();

			void OnKeyPress();
			void OnKeyDown();
			void OnKeyUp();
			void OnKeyHold();

			void OnMousePress();
			void OnMouseDown();
			void OnMouseUp();
			void OnMouseHold();
			void OnMouseMove();

		private:
			Keyboard m_keyboard;
			Mouse m_mouse;
	};
}