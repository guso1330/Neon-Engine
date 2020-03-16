#include "MacOSWindow.h"

/*
	TODO:
	- Abstract GLFW out of this class
 	- figure out a way to do better input that can be defined outside of the window class
 	- Handle full screen windows and multiple monitors
*/
namespace Neon {
	MacOSWindow::MacOSWindow(const WindowSettings &settings) {
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
		m_title(title)
	{
		m_vsyncEnabled = false;
		RunInit();
	}

	MacOSWindow::~MacOSWindow() {
		GLFW::GLFWContext::GetInstance().Destroy();
	}

	void MacOSWindow::Update() {
		std::pair<int, int> dimensions = GLFW::GLFWContext::GetInstance().Update();
		m_width = dimensions.first;
		m_height = dimensions.second;
	}

	void MacOSWindow::Close() {
		GLFW::GLFWContext::GetInstance().Close();
	}

	/* Getters */
	bool MacOSWindow::isClosed() const {
		return GLFW::GLFWContext::GetInstance().isCurrentWindowClosed();
	}

	/* Setters */
	void MacOSWindow::SetSize(unsigned int width, unsigned int height) {
		m_width = width;
		m_height = height;
		GLFW::GLFWContext::GetInstance().SetWindowDimensions(width, height);
	}

	void MacOSWindow::SetFullscreen(bool isFullscreen) {
		m_isFullscreen = isFullscreen;
		// TODO: set up full screen window
	}

	void MacOSWindow::SetVSync(bool enabled) {
		GLFW::GLFWContext::GetInstance().SetVSync(enabled);

		m_vsyncEnabled = enabled;
	}

	void MacOSWindow::SetTitle(const std::string& title) {
		GLFW::GLFWContext::GetInstance().SetTitle(title.c_str());
	}

	void MacOSWindow::SetInputMode(int mode, int value) {
		GLFW::GLFWContext::GetInstance().SetInputMode(mode, value);
	}

	/* Private Initializers */
	void MacOSWindow::RunInit() {
		if (!Init()) {
			NE_CORE_ERROR("MacOSWindow: Window did not initialize");
			GLFW::GLFWContext::GetInstance().Destroy();
		}
	}

	bool MacOSWindow::Init() {
		GLFW::GLFWwindowSettings settings;
		bool initialized = false;

		initialized = GLFW::GLFWContext::GetInstance().CreateContext();

		if (initialized) {
			settings.width = m_width;
			settings.height = m_height;
			settings.title = m_title;
			m_Window = GLFW::GLFWContext::GetInstance().CreateWindow(
				settings,
				this
			);

			if (m_Window != nullptr) {
				/* Initialize all events */
				InitEvents();

				/* NOTE: For now, i'm leaving the callback calls as inline functions */
				/* Set all callbacks */
				glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* glfwWindow, int width, int height) {
					EventManager::GetInstance().DispatchEvent(NEON_EVENT_WINDOW_RESIZE, width, height);
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
			}

		}

		return initialized;
	}

	void MacOSWindow::InitEvents() {
		/* WindowResize Event */
		EventManager::GetInstance().AddEvent(NEON_EVENT_WINDOW_RESIZE, EventPtr(new WindowResizeEvent()));
		EventManager::GetInstance().AddEventHandler(NEON_EVENT_WINDOW_RESIZE, WindowResizeCallback(
			// TODO replace this function with a more meaningful resize function
			[](int width, int height) {
				NE_CORE_INFO("WindowResize Event 1: Resize occurred {}, {}", width, height);
			}
		));
	}
}
