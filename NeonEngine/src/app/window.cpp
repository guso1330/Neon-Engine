#include "window.h"

namespace neon {

	void windowResize(GLFWwindow *window, int width, int height);

	Window::Window(unsigned int width, unsigned int height, bool fullscreen, const char* title) :
		m_width(width),
		m_height(height),
		m_fullscreen(fullscreen),
		m_title(title) {
		if (!init()) {
			std::cerr << "Error: window did not initialize" << std::endl;
			glfwTerminate();
		}
	}

	Window::~Window() {
		glfwTerminate();
	}

	bool Window::init() {
		if (!glfwInit()) {
			std::cerr << "Failed to initalize GLFW" << std::endl;
			return false;
		}

		/* Setting meta data for the window properties */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		#ifdef __APPLE__ // handle mac compatibility
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif
		/* glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); */

		/* Create variable to store the window */
		m_window = glfwCreateWindow(m_width, m_height, "Neon Engine", nullptr, nullptr);

		/* Check if the window has opened */
		if (m_window == nullptr) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			return false;
		}

		/* Set the newly created window to the current context */
		glfwMakeContextCurrent(m_window);
		glfwSetWindowSizeCallback(m_window, windowResize);

		/* Setting up glad and initializing it */
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		/* Print Renderer and OpenGL info */
		const GLubyte *renderer = glGetString(GL_RENDERER);
		const GLubyte *version = glGetString(GL_VERSION);
		std::cout << "Neon Engine - Version 0.1" << std::endl;
		std::cout << "Renderer: " << renderer << std::endl;
		std::cout << "OpenGL Version: " << version << std::endl;

		return true;
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(m_window) == 1;
	}

	void Window::update() {
		glfwPollEvents();
		glfwGetFramebufferSize(m_window, &m_width, &m_height);
		glfwSwapBuffers(m_window);
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::setClearColor(float r, float g, float b, float a) {
		glClearColor(r, g, b, a);
	}

	void windowResize(GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
	}

}