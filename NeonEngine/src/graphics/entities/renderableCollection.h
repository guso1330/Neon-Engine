#pragma once

#include "./renderable3d.h"
#include "../../shaders/program.h"
#include "../buffers/vertexArray.h"
#include "../buffers/vertexBuffer.h"

#include <glad/glad.h>
#include <vector>
#include <iostream>

#define MAX_ELEMENTS 	7812
#define MAT4_SIZE  		sizeof(glm::mat4)
#define BUFFER_SIZE 	MAX_ELEMENTS * MAT4_SIZE // ~0.5MB

/*
	Class that utilizes instanced rendering
*/
namespace neon {

	class RenderableCollection {
		public:
			RenderableCollection(Renderable3d *renderable, Program *program);
			~RenderableCollection();
			
			void HandleBufferData();
			void SetTransforms(std::vector<Transform> &n_transforms);
			void UpdateAllTransforms(std::vector<Transform> &transforms, Transform &transform);
			void Draw();

		private:
			void Init();

		private:
			Program *m_program;			
			Renderable3d *m_renderable;
			VertexArray *m_vao;
			VertexBuffer *m_vbo;
			VertexBufferLayout m_layout;

			std::vector<glm::mat4> m_transforms;
			glm::mat4 m_modelMatrix;
			
			int m_size_factor = 1;
			unsigned int m_transformLoc;
			

	};
}