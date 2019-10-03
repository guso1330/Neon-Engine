#pragma once

// TODO: Implement key codes for Neon Engine (Pull from GLFW key codes)

#include "keyboard.h"
#include "mouse.h"
#include "../timer.h"

namespace Neon {
	class Input {
		public:
			Input();
			~Input() = default;

			/* Getters */
			inline static Timestep GetElapsedTime() { return s_Timer.GetElapsedTime(); }

			/* Keyboard functions */
			inline const bool IsKeyDown(int key) const { return m_Keyboard.GetKey(key); }
			inline const bool IsKeyUp(int key)   const { return !m_Keyboard.GetKey(key); }

			/* Mouse functions */
			inline const glm::vec2 GetCursorPosition()  const { return m_Mouse.GetPosition(); }
			inline const bool IsMouseDown(int key) const { return m_Mouse.GetButton(key); }
			inline const bool IsMouseUp(int key)   const { return !m_Mouse.GetButton(key); }

			/* Event functions */
			void KeyboardEvent(const int key, const int action, const int mods);
			void MousePressEvent(const int button, const int action, const int mods);
			void MouseCursorEvent(int x, int y);

			/* Member Functions */
			void InitEvents();

		private:
			// Note: Each input class only has one associated mouse and keyboard
			Keyboard m_Keyboard;
			Mouse m_Mouse;
		private:
			static Timer s_Timer;
	};
}
