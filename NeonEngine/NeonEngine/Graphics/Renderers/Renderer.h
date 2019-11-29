#pragma once

#include "Core/Core.h"

// OpenGL
#include "Core/Platforms/OpenGL/OpenGLContext.h"

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

namespace Neon {
	struct RenderMatrices {
		glm::mat4 transform;
		glm::mat4 viewProjection;
	};

	class Renderer {
		public:
			/* Constructors */
			Renderer(Renderer const&) = delete;

			/* Operator Overrides */
			void operator=(Renderer const&) = delete;

			/* Methods */
			static void Init();
			void Clear() const;
			void Submit(std::shared_ptr<IVertexArray>& va, std::shared_ptr<IProgram>& program, const RenderMatrices& mats);

			/* Getters */
			static Renderer& GetInstance();
			inline static IRendererAPI::API GetAPI() { return IRendererAPI::GetAPI(); }

		/* Private Methods */
		private:
			Renderer() {}
			static bool Instantiate();
			static IRendererAPI& GetRendererAPIInstance();

		/* Private static Variables */
		private:
			static bool s_initialized;
	};
}
