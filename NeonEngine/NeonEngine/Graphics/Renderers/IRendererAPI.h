#pragma once

#include "Graphics/Renderers/IVertexArray.h"

namespace Neon {
	class IRendererAPI
	{
		public:
			enum class API {
				NONE = 0,
				OPENGL = 1
			};

		public:
			/* Methods */
			virtual void Clear() = 0;
			virtual void DrawIndexed(const std::shared_ptr<IVertexArray>& va) = 0;

			/* Setters */
			virtual void SetClearColor(float r, float g, float b, float a) = 0;

			/* Getters */
			inline static API GetAPI() { return s_API; }

		private:
			static API s_API;
	};
}