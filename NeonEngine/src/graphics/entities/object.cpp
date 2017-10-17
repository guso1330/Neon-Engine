#include "object.h"

namespace neon {
	Object::Object(const char *filename) {
		mesh = new Mesh(filename);
	}

	Object::~Object() { delete mesh; }
}