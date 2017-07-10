#include "window.h"

namespace neon {
	Window::Window(const unsigned int width, const unsigned int height, const std::string& name) {
		m_Width = width;
		m_Height = height;
		m_Name = name;
		InitWindow();
	}

	void Window::InitWindow() {
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

		GLFWwindow *window = glfwCreateWindow((int)m_Width, (int)m_Height, m_Name.c_str(), nullptr, nullptr);
	}
}