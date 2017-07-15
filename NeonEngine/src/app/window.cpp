#include "window.h"

namespace neon {
	Window::Window(unsigned int width, unsigned int height, bool fullscreen, const char* title) :
		m_width(width),
		m_height(height),
		m_fullscreen(fullscreen),
		m_title(title) {
		if (!init()) {
			std::cerr << "Error: window did not initialize" << std::endl;
		}
	}

	bool Window::init() {
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow *window = glfwCreateWindow(m_width, m_height, "Neon Engine", nullptr, nullptr);

		int screenWidth, screenHeight;
		// accurate value to the width of the screen relative to screen size
		glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

		if (window == nullptr) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			glfwTerminate();

			return EXIT_FAILURE;
		}

		glfwMakeContextCurrent(window);

		// Basically use GLEW the modern way
		glewExperimental = GL_TRUE;
		if (GLEW_OK != glewInit()) {
			std::cerr << "Failed to initialize GLEW" << std::endl;

			return EXIT_FAILURE;
		}

		glViewport(0, 0, screenWidth, screenHeight);
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// NOTE: draw opengl stuff
			glfwSwapBuffers(window);
		}

		glfwTerminate();
	}
}