#include "Core/Core.h"
#include "Graphics/Renderers/IRendererAPI.h"

#include "nepch.h"

namespace Neon {
	#ifdef NE_PLATFORM_MACOS
		IRendererAPI::API IRendererAPI::s_API = IRendererAPI::API::OPENGL;
	#endif
} // Neon
