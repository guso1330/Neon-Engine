#include "window.h"

// TODO: figure out a way to do better input that can be defined outside of the window class

namespace neon {

	static void window_resize_callback(GLFWwindow *window, int width, int height);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouse_cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos);
	static void mouse_button_callback (GLFWwindow *window, int button, int action, int mods);

	Window::Window(unsigned int width, unsigned int height, bool fullscreen, const char* title) :
		m_width(width),
		m_height(height),
		m_fullscreen(fullscreen),
		m_title(title) {
		if (!Init()) {
			std::cerr << "Error: window did not initialize" << std::endl;
			glfwTerminate();
		}
	}

	Window::~Window() {
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	bool Window::Init() {
		if (!glfwInit()) {
			std::cerr << "Failed to initalize GLFW" << std::endl;
			return false;
		}

		/* Setting meta data for the window properties */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        #ifdef __APPLE__ // handle mac compatibility
            std::cout << "Setting MacOS forward compatibility" << std::endl;
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		/* Create variable to store the window */
		m_window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

		/* Check if the window has opened */
		if (m_window == nullptr) {
			std::cerr << "Failed to create GLFW window" << std::endl;
			return false;
		}

		/* Set the newly created window to the current context */
		glfwMakeContextCurrent(m_window);

		/* Set all callbacks */
		glfwSetWindowSizeCallback(m_window, window_resize_callback);
		glfwSetKeyCallback(m_window, key_callback);
		glfwSetCursorPosCallback(m_window, mouse_cursor_position_callback);
		glfwSetMouseButtonCallback(m_window, mouse_button_callback);

		// WARNING
		// Eliminate the frame cap
		glfwSwapInterval(0.0);

		/* Setting up glad and initializing it */
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
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

	bool Window::isClosed() const {
		return glfwWindowShouldClose(m_window) == 1;
	}

	void Window::Update() {
		glfwPollEvents();
		glfwGetFramebufferSize(m_window, &m_width, &m_height);
		glfwSwapBuffers(m_window);
	}

	void Window::Clear() const {
		GL_Call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_Call(glFlush());
	}

	void Window::SetClearColor(float r, float g, float b, float a) {
		GL_Call(glClearColor(r, g, b, a));
	}

	/*******************************
	* Static functions - Callbacks *
	*******************************/
	static void window_resize_callback(GLFWwindow *window, int width, int height) {
		GL_Call(glViewport(0, 0, width, height));
	}

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {

		std::cout << "Key: " << key << std::endl;
		std::cout << "Scancode: " << scancode << std::endl;
		std::cout << "Action: " << action << std::endl;
		std::cout << "Mods: " << mods << std::endl;

		// Close the window
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
	}

	static void mouse_cursor_position_callback(GLFWwindow *window, double x_pos, double y_pos) {
		
	}

	static void mouse_button_callback (GLFWwindow *window, int button, int action, int mods) {
	}
}
