#include "MacOSWindow.h"

/*
	TODO:
	- Abstract GLFW out of this class
 	- figure out a way to do better input that can be defined outside of the window class
 	- Handle full screen windows and multiple monitors
*/
namespace Neon {
	MacOSWindow::MacOSWindow(const WindowSettings &settings) :
		m_Input(new Input())
	{
		m_title = settings.title;
		m_width = settings.width;
		m_height = settings.height;
		m_isFullscreen = settings.fullscreen;
		m_vsyncEnabled = false;

		RunInit();
	}

	MacOSWindow::MacOSWindow(std::string title, unsigned int width, unsigned int height, bool fullscreen) :
		m_width(width),
		m_height(height),
		m_isFullscreen(fullscreen),
		m_title(title),
		m_Input(new Input())
	{
		m_vsyncEnabled = false;
		RunInit();
	}

	MacOSWindow::~MacOSWindow() {
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void MacOSWindow::Update() {
		glfwGetFramebufferSize(m_Window, (int*)&m_width, (int*)&m_height);
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	void MacOSWindow::Close() {
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
	}

	/* Getters */
	bool MacOSWindow::isClosed() const {
		return glfwWindowShouldClose(m_Window) == 1;
	}

	/* Setters */
	void MacOSWindow::SetSize(unsigned int width, unsigned int height) {
		glfwSetWindowSize(m_Window, width, height);
		glfwGetWindowSize(m_Window, (int*)&m_width, (int*)&m_height);
	}

	void MacOSWindow::SetFullscreen(bool isFullscreen) {
		m_isFullscreen = isFullscreen;
		// TODO: set up full screen window
	}

	void MacOSWindow::SetVSync(bool enabled) {
		if (enabled) {
			glfwSwapInterval(1);
		} else {
			glfwSwapInterval(0);
		}

		m_vsyncEnabled = enabled;
	}

	void MacOSWindow::SetInputMode(int mode, int value) {
		glfwSetInputMode(m_Window, mode, value);
	}

	/* Private Initializers */
	void MacOSWindow::RunInit() {
		if (!Init()) {
			NE_CORE_ERROR("Window did not initialize");
			glfwTerminate();
		}
	}

	bool MacOSWindow::Init() {
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
		m_Window = glfwCreateWindow((int)m_width, (int)m_height, m_title.c_str(), nullptr, nullptr);

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
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* glfwWindow, int width, int height) {
			EventManager::DispatchEvent(NEON_EVENT_WINDOW_RESIZE, width, height);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
			void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
			MacOSWindow *window = static_cast<MacOSWindow *>(ptr_window);
			// TODO: Pass arguments from the window object ot this
			//		 event function
			window->GetInput()->KeyboardEvent(key, action, mods);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow *glfwWindow, double x_pos, double y_pos) {
			void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
			MacOSWindow *window = static_cast<MacOSWindow *>(ptr_window);

			window->GetInput()->MouseCursorEvent(x_pos, y_pos);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *glfwWindow, int button, int action, int mods) {
			void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
			MacOSWindow *window = static_cast<MacOSWindow *>(ptr_window);
			// TODO: Pass arguments from the window object ot this
			//		 event function

			window->GetInput()->MousePressEvent(button, action, mods);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow *glfwWindow, double xoffset, double yoffset) {});

		return true;
	}

	void MacOSWindow::InitEvents() {
		/* WindowResize Event */
		EventManager::AddEvent(NEON_EVENT_WINDOW_RESIZE, EventPtr(new WindowResizeEvent()));
		EventManager::AddEventHandler(NEON_EVENT_WINDOW_RESIZE, WindowResizeCallback(
			// TODO replace this function with a more meaningful resize function
			[](int width, int height) {
				NE_CORE_INFO("WindowResize Event 1: Resize occurred {}, {}", width, height);
			}
		));
	}
}
