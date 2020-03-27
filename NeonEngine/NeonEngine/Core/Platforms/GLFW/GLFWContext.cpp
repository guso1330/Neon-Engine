#include "GLFWContext.h"

namespace Neon { namespace GLFW {
	bool GLFWContext::s_initialized = false;

	bool GLFWContext::CreateContext() {
		NE_CORE_ASSERT((s_initialized == false), "Can't reinitialize GLFW");

		if (!glfwInit()) {
			NE_CORE_ERROR("GLFW: Failed to initalize GLFW");
			return false;
		}

		s_initialized = true;

		/* Setting meta data for the window properties */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		#ifdef NE_PLATFORM_MACOS // handle mac compatibility
			NE_CORE_WARN("GLFW: Setting MacOS forward compatibility");
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
		#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		return true;
	}

	GLFWwindow* GLFWContext::CreateWindow(const GLFWwindowSettings& settings, void* userPointer) {
		GLFWwindow* window = glfwCreateWindow(
			settings.width,
			settings.height,
			settings.title.c_str(),
			settings.monitor,
			settings.share
		);

		if (window == nullptr) {
			NE_CORE_ERROR("GLFW: Failed to create window");
		} else {
			glfwSetWindowUserPointer(window, userPointer);
			glfwMakeContextCurrent(window);
		}

		return window;
	}

	std::pair<int, int> GLFWContext::Update() {
		GLFWwindow* current_window = glfwGetCurrentContext();
		int width;
		int height;

		glfwGetFramebufferSize(current_window, &width, &height);
		glfwSwapBuffers(current_window);
		glfwPollEvents();

		return std::make_pair(width, height);
	}

	void GLFWContext::Close() {
		glfwSetWindowShouldClose(glfwGetCurrentContext(), GLFW_TRUE);
	}

	void GLFWContext::Destroy() {
		glfwDestroyWindow(glfwGetCurrentContext());
		glfwTerminate();
	}

	GLFWContext& GLFWContext::GetInstance() {
		static GLFWContext instance;
		return instance;
	}

	void GLFWContext::SetWindowHint(int hint, int value) {
		glfwWindowHint(hint, value);
	}

	void GLFWContext::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}
	}

	void GLFWContext::SetWindowDimensions(unsigned int width, unsigned int height) {
		glfwSetWindowSize(glfwGetCurrentContext(), width, height);
	}

	void GLFWContext::SetTitle(const char* title) {
		glfwSetWindowTitle(glfwGetCurrentContext(), title);
	}

	void GLFWContext::SetInputMode(int mode, int value) {
		glfwSetInputMode(glfwGetCurrentContext(), mode, value);
	}
}}
