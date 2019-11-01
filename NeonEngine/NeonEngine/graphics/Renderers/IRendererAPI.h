#pragma once

#include "Graphics/Renderers/IVertexArray.h"

namespace Neon {
	class IRendererAPI
	{
		public:
			enum API {

			};

		public:
			/* Methods */
			virtual void Clear() = 0;
			virtual void DrawIndexed(const std::shared_ptr<IVertexArray>& va) = 0;

			/* Getters */
			static API GetAPI() { return s_API; }

			/* Setters */
			virtual void SetClearColor(float r, float g, float b, float a) = 0;

		private:
			static API s_API;
	};
}