#include "Core/Platforms/MacOS/MacOSWindow.h"
#include "Core/Platforms/OpenGL/OpenGLContext.h"

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

				/*
					NOTE: For now, i'm leaving the callback calls as inline functions

					TODO:
					- Set all callbacks
				*/
				glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* glfwWindow, int width, int height) {
					EventManager::GetInstance().DispatchEvent(NEON_EVENT_WINDOW_RESIZE, width, height);
				});

				glfwSetKeyCallback(m_Window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
					void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
					MacOSWindow *window = static_cast<MacOSWindow *>(ptr_window);

					window->GetInput()->KeyboardEvent(key, scancode, action, mods);
				});

				glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *glfwWindow, int button, int action, int mods) {
					void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
					MacOSWindow *window = static_cast<MacOSWindow *>(ptr_window);

					window->GetInput()->MousePressEvent(button, action, mods);
				});

				glfwSetCursorPosCallback(m_Window, [](GLFWwindow *glfwWindow, double x_pos, double y_pos) {
					void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
					MacOSWindow *window = static_cast<MacOSWindow *>(ptr_window);

					window->GetInput()->MouseCursorEvent(x_pos, y_pos);
				});

				glfwSetScrollCallback(m_Window, [](GLFWwindow *glfwWindow, double xoffset, double yoffset) {
					void *ptr_window = glfwGetWindowUserPointer(glfwWindow);
					MacOSWindow *window = static_cast<MacOSWindow*>(ptr_window);

					window->GetInput()->MouseScrollEvent(xoffset, yoffset);
				});
			}

		}

		return initialized;
	}

	void MacOSWindow::InitEvents() {
		/* WindowResize Event */
		EventManager::GetInstance().AddEventHandler(NEON_EVENT_WINDOW_RESIZE, WindowResizeCallback(
			[](unsigned int width, unsigned int height) {
				GLFW::GLFWContext::GetInstance().SetWindowDimensions(width, height);
				OpenGL::OpenGLContext::GetInstance().ResizeViewport(width, height);
				NE_CORE_INFO("WindowResize Event: Resize occurred {}, {}", width, height);
			}
		));
	}

	/* Public Methods */
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
}
