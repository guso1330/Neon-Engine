#pragma once

#include "keyboard.h"
#include "mouse.h"

namespace Neon {
	class Input {
		public:
			Input();
			~Input() = default;

			/* Getters */

			/* Keyboard functions */
			inline const bool IsKeyDown(int key) const { return m_keyboard.GetKey(key); }
			inline const bool IsKeyUp(int key)   const { return !m_keyboard.GetKey(key); }

			/* Mouse functions */
			inline const glm::vec2 GetCursorPosition()  const { return m_mouse.GetPosition(); }
			inline const bool IsMouseDown(int key) const { return m_mouse.GetButton(key); }
			inline const bool IsMouseUp(int key)   const { return !m_mouse.GetButton(key); }

			/* Event functions */
			void KeyboardEvent(const int key, const int action, const int mods);
			void MousePressEvent(const int button, const int action, const int mods);
			void MouseCursorEvent(int x, int y);

			/* Member Functions */
			void InitEvents();

		private:
			// Note: Each input class only has one associated mouse and keyboard
			Keyboard m_keyboard;
			Mouse m_mouse;
	};
}
