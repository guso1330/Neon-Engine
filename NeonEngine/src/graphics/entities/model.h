#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../../shaders/texture.h"
#include "./mesh.h"
#include "./renderable3d.h"

namespace neon {

	class Model : public Renderable3d {
	public:
		Model(const char *filename, Program* program, bool shouldSendData = true);
		~Model();

		// GETTERS
		inline const Mesh* GetMesh() const { return m_mesh; }

	private:
		void BuildVertexData();

	private:
		/* 
			TODO: Maybe I shouldn't declare this on the heap...?
		*/
		Mesh *m_mesh;
	};
}