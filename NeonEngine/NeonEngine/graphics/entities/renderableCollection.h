#pragma once

#include "Graphics/Entities/renderable3d.h"
#include "Graphics/Entities/mesh.h"
#include "Graphics/Entities/model.h"
#include "Core/Platforms/OpenGL/program.h"
#include "Core/Platforms/OpenGL/VertexBuffer.h"
#include "Core/Platforms/OpenGL/VertexArray.h"

#include <glad/glad.h>
#include <vector>
#include <iostream>

#define MAX_ELEMENTS 	7812
#define MAT4_SIZE  		sizeof(glm::mat4)
#define BUFFER_SIZE 	MAX_ELEMENTS * MAT4_SIZE // ~0.5MB

/*
	Class that utilizes instanced rendering
*/
namespace Neon {

	class RenderableCollection {
		public:
			RenderableCollection(Renderable3d *renderable, Program *program);
			RenderableCollection(Model *model, Program *program);

			~RenderableCollection();
			
			void HandleBufferData();
			void SetTransforms(std::vector<Transform> &n_transforms);
			void UpdateAllTransforms(std::vector<Transform> &transforms, Transform &transform);
			void Draw() const;
			void Draw(const std::vector<Mesh*> &meshes) const;

		private:
			void Init();

		private:
			Renderable3d *m_renderable;
			Model *m_model;
			
			Program *m_program;			

			VertexArray *m_vao;
			VertexBuffer *m_vbo;
			BufferLayout m_layout;

			std::vector<glm::mat4> m_transforms;
			glm::mat4 m_modelMatrix;
			
			int m_size_factor = 1;
			unsigned int m_transformLoc;
	};
}