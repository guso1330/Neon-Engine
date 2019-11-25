#pragma once

#include "Core/Core.h"

// Interfaces
#include "Graphics/Renderers/IRendererAPI.h"
#include "Graphics/Renderers/IVertexArray.h"
#include "Graphics/Renderers/IProgram.h"
#include "Graphics/Renderers/ITexture.h"
#include "Graphics/Renderers/BufferLayout.h"

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
		/* Private static Variables */
		private:
			static bool s_initialized;
	};
}
