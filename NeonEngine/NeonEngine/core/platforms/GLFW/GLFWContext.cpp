#include "GLFWContext.h"
#include "../../Core.h"

#include "nepch.h"

namespace Neon {
	void GLFWContext::CreateContext() {
		if (!glfwInit()) {
			NE_CORE_ERROR("Failed to initalize GLFW");
			// return false;
		}

		/* Setting meta data for the window properties */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		#ifdef NE_PLATFORM_MACOS // handle mac compatibility
			NE_CORE_WARN("Setting MacOS forward compatibility");
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);
	}
}
