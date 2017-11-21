#pragma once

#include "../entities/renderable3d.h"
#include <vector>

namespace neon {

#define RENDERER_MAX_VERTICES 60000
#define RENDERER_VERTEX_SIZE sizeof(Vertex)
#define RENDERER_BUFFER_SIZE RENDERER_MAX_VERTICES * RENDERER_VERTEX_SIZE

#define SHADER_VERTEX_INDEX 0
#define SHADER_TEX_INDEX	1

	class ForwardRenderer {
		public:
			ForwardRenderer();
			~ForwardRenderer();

			void Begin();
			void Submit(Renderable3d* renderable);
			void End();
			void Flush();

		private:
			void Init();

		private:
			GLuint m_vao;
			GLuint m_vbo;
			IndexBuffer *m_ibo;

			// Data
			Vertex* m_buffer;
			std::vector<Vertex> m_vertexData;
	};
}