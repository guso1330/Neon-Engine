// TODO: make a macro function that supports returned values

#pragma once

#include <glad/glad.h>

#include "nepch.h"

#ifdef _WIN32
	#define DEBUG_BREAK __debugbreak()
#else
	#define DEBUG_BREAK raise(SIGTRAP)
#endif

#define GL_ASSERT(x) if(!(x)) DEBUG_BREAK;
#define GL_Call(x) GLClearError();\
	x;\
	GL_ASSERT(GLLogCall(#x, __FILE__, __LINE__))

namespace Neon {
	static void GLClearError() {
		while (glGetError() != GL_NO_ERROR);
	}

	static bool GLLogCall(const char* function, const char* file, int line) {
		while(GLenum error = glGetError()) {
			std::cout << "WARNING OpenGL Error (" << error << "): " << function << " " << file << ": " << line << std::endl;
			return false;
		}
		return true;
	}
}