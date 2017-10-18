#include "model.h"

namespace neon {
	Model::Model(const char *filename) {
		mesh = new Mesh(filename);
	}

	Model::~Model() { delete mesh; }
}