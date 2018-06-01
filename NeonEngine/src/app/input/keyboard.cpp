#include "keyboard.h"

namespace neon {
	Keyboard::Keyboard() {
		for(int i=0; i < MAX_KEYS; ++i) {
			m_keys[i] = false;
		}
	}
	
	Keyboard::~Keyboard() {}
}