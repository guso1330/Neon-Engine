#pragma once

#include "Core/Core.h"
#include "Core/Types/Singleton.h"
#include "Core/Platforms/OpenGL/OpenGLContext.h" // OpenGL

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Neon {
	struct RenderMatrices {
		glm::mat4 transform;
		glm::mat4 viewProjection;
	};

	class Renderer : public Singleton {
		public:
			/* Methods */
			bool Init();
			void Clear() const;
			void Submit(IVertexArray* va, IProgram* program, RenderMatrices mats);
			void Flush();

			/* Getters */
			static Renderer& GetInstance();
			inline static IRendererAPI::API GetAPI() { return IRendererAPI::GetAPI(); }

		/* Private Methods */
		private:
			static bool Instantiate();
			IRendererAPI& GetRendererAPIInstance() const;

		/* Private static Variables */
		private:
			static bool s_initialized;
	};
}
