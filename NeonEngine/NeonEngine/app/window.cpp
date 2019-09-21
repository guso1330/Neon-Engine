#include "window.h"

/*
	TODO: 
 	- figure out a way to do better input that can be defined outside of the window class
 	- Abstract out GLFW from this class to make more generic
*/

namespace Neon {
	static void window_resize_callback(GLFWwindow *glfwWindow, int width, int height);
	static void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods);
	static void mouse_cursor_position_callback(GLFWwindow *glfwWindow, double x_pos, double y_pos);
	static void mouse_button_callback (GLFWwindow *glfwWindow, int button, int action, int mods);
	static void scroll_callback(GLFWwindow* glfwWindow, double xoffset, double yoffset);

	Window::Window(unsigned int width, unsigned int height, bool fullscreen, const char* title) :
		m_width(width),
		m_height(height),
		m_fullscreen(fullscreen),
		m_title(title),
		m_Input(new Input())
	{
		RunInit();
	}

	Window::Window(const WindowSettings &settings) :
		m_Input(new Input())
	{
		m_width = settings.width;
		m_height = settings.height;
		m_fullscreen = settings.fullscreen;
		m_title = settings.title;

		RunInit();
	}

	Window::~Window() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::RunInit() {
		if (!Init()) {
			NE_CORE_ERROR("Window did not initialize");
			glfwTerminate();
		}
	}

	bool Window::Init() {
		if (!glfwInit()) {
			NE_CORE_ERROR("Failed to initalize GLFW");
			return false;
		}

		/* Setting meta data for the window properties */
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		#ifdef __APPLE__ // handle mac compatibility
			NE_CORE_WARN("Setting MacOS forward compatibility");
			glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		#endif
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_SAMPLES, 4);

		/* Create variable to store the window */
		m_Window = glfwCreateWindow(m_width, m_height, m_title, nullptr, nullptr);

		/* Check if the window has opened */
		if (m_Window == nullptr) {
			NE_CORE_ERROR("Failed to create GLFW window");
			return false;
		}

		// Assign the user pointer to this
		glfwSetWindowUserPointer(m_Window, this);

		/* Set the newly created window to the current context */
		glfwMakeContextCurrent(m_Window);

		/* Initialize all events */
		InitEvents();

		/* Set all callbacks */
		glfwSetWindowSizeCallback(m_Window, window_resize_callback);
		glfwSetKeyCallback(m_Window, key_callback);
		glfwSetCursorPosCallback(m_Window, mouse_cursor_position_callback);
		glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
		glfwSetScrollCallback(m_Window, scroll_callback);

		// WARNING
		// TODO: Eliminate the frame cap
		glfwSwapInterval(0.0);

		return true;
	}

	void Window::InitEvents() {
		/* WindowResize Event */
		EventManager::AddEvent(NEON_EVENT_WINDOW_RESIZE, EventPtr(new WindowResizeEvent()));
		EventManager::AddEventHandler(NEON_EVENT_WINDOW_RESIZE, WindowResizeCallback(
			// TODO replace this function with a more meaningful resize function
			[](int width, int height) {
				// NE_CORE_INFO("WindowResize Event 1: Resize occurred {}, {}", width, height);
			}
		));
	}

	void Window::SetInputMode(int mode, int value) {
		glfwSetInputMode(GetCurrentWindow(), mode, value);
	}

	void Window::SetSize(unsigned int width, unsigned int height) {
		GLFWwindow* window = GetCurrentWindow();
		glfwSetWindowSize(window, width, height);
		glfwGetWindowSize(window, &m_width, &m_height);
	}

	bool Window::isClosed() const {
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void Window::Update() {
		glfwGetFramebufferSize(m_Window, &m_width, &m_height);
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void Window::Close() {
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
	}

	/*******************************
	* Static functions - Callbacks *
	*******************************/
	void window_resize_callback(GLFWwindow *glfwWindow, int width, int height) {
		void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
		Window *window = static_cast<Window *>(ptr_window);

		EventManager::DispatchEvent(NEON_EVENT_WINDOW_RESIZE, width, height);
	}

	void key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
		void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
		Window *window = static_cast<Window *>(ptr_window);

		// TODO: Pass arguments from the window object ot this
		//		 event function
		window->GetInput()->KeyboardEvent(key, action, mods);
	}

	void mouse_cursor_position_callback(GLFWwindow *glfwWindow, double x_pos, double y_pos) {
		void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
		Window *window = static_cast<Window *>(ptr_window);

		window->GetInput()->MouseCursorEvent(x_pos, y_pos);
	}

	void mouse_button_callback(GLFWwindow *glfwWindow, int button, int action, int mods) {
		void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
		Window *window = static_cast<Window *>(ptr_window);

		// TODO: Pass arguments from the window object ot this
		//		 event function
		window->GetInput()->MousePressEvent(button, action, mods);
	}

	void scroll_callback(GLFWwindow *glfwWindow, double xoffset, double yoffset) {
		void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
		Window *window = static_cast<Window *>(ptr_window);
	}
}
