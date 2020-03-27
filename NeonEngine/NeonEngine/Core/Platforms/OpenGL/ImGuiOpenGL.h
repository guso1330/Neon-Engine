#pragma once

#include "imgui.h"

// Backend API
IMGUI_IMPL_API bool     ImGui_ImplOpenGL3_Init(const char* glsl_version = NULL);
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_Shutdown();
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_NewFrame();
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_RenderDrawData(ImDrawData* draw_data);

IMGUI_IMPL_API bool     ImGui_ImplOpenGL3_CreateFontsTexture();
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_DestroyFontsTexture();
IMGUI_IMPL_API bool     ImGui_ImplOpenGL3_CreateDeviceObjects();
IMGUI_IMPL_API void     ImGui_ImplOpenGL3_DestroyDeviceObjects();

#if !defined(IMGUI_IMPL_OPENGL_LOADER_GL3W) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLEW) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLAD) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3) \
 && !defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)
    #if defined(__has_include)
        #if __has_include(<GL/glew.h>)
            #define IMGUI_IMPL_OPENGL_LOADER_GLEW
        #elif __has_include(<glad/glad.h>)
            #define IMGUI_IMPL_OPENGL_LOADER_GLAD
        #elif __has_include(<GL/gl3w.h>)
            #define IMGUI_IMPL_OPENGL_LOADER_GL3W
        #elif __has_include(<glbinding/glbinding.h>)
            #define IMGUI_IMPL_OPENGL_LOADER_GLBINDING3
        #elif __has_include(<glbinding/Binding.h>)
            #define IMGUI_IMPL_OPENGL_LOADER_GLBINDING2
        #else
            #error "Cannot detect OpenGL loader!"
        #endif
    #else
        #define IMGUI_IMPL_OPENGL_LOADER_GL3W // Default to GL3W
    #endif
#endif
