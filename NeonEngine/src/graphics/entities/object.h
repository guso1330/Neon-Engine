#pragma once

#include <glad/glad.h>
#include "./mesh.h"

namespace neon {
	class Object {
		public:
			Object(const char *filename);
			~Object();

			inline Mesh* GetMesh() const { return mesh; }
		private:
			Mesh *mesh;
	};
}