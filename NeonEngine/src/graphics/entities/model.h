#pragma once

#include <glad/glad.h>
#include "./mesh.h"

namespace neon {
	class Model {
		public:
			Model(const char *filename);
			~Model();

			inline Mesh* GetMesh() const { return mesh; }
		private:
			Mesh *mesh;
	};
}