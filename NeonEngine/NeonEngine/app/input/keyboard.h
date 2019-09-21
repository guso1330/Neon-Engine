#pragma once

#define MAX_KEYS 1024

#include <glm/glm.hpp>

#include <iostream>
#include <algorithm>

namespace Neon {

	enum KeyEvents {
		NEON_KEY_UP,
		NEON_KEY_DOWN,
		NEON_KEY_HOLD
	};

	class Keyboard {
		public:
			Keyboard();

			~Keyboard();

			inline const bool GetKey(const int key) const { return m_keys[key]; }
			inline void SetKey(const int key, const bool state) { m_keys[key] = state; }

		private:
			bool m_keys[MAX_KEYS];
	};
}