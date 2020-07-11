#include "nepch.h"

#include "Core/Core.h"
#ifdef NE_PLATFORM_MACOS
	#define IMGUI_IMPL_OPENGL_LOADER_GLAD
	#include <examples/imgui_impl_opengl3.cpp>
	#include <examples/imgui_impl_glfw.cpp>
#elif defined(NE_PLATFORM_WIN64)
	#define IMGUI_IMPL_OPENGL_LOADER_GLAD
	#include <examples/imgui_impl_opengl3.cpp>
	#include <examples/imgui_impl_glfw.cpp>
#endif
