#pragma once

/*
	GLFWContext (Singleton)

	NOTE:
		- Is this class needed?
		- Is it fine for each implementation to handle GLFW on it's own?
*/
#include "Core/Types/Singleton.h"
#include "nepch.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Neon { namespace GLFW {
	struct GLFWwindowSettings {
		int width;
		int height;
		std::string title;
		GLFWmonitor* monitor;
		GLFWwindow* share;

		GLFWwindowSettings() :
			width(1280),
			height(720),
			title(""),
			monitor(nullptr),
			share(nullptr)
		{}
	};

	class GLFWContext : public Singleton {
		public:
			/* Implementation functions */
			bool CreateContext();
			GLFWwindow* CreateWindow(
				const GLFWwindowSettings& settings = GLFWwindowSettings(),
				void* userPointer = nullptr
			);
			std::pair<int, int> Update();
			void Close();
			void Destroy();

			/* Getters */
			static GLFWContext& GetInstance();
			inline GLFWwindow* GetCurrentWindow() { return glfwGetCurrentContext(); }
			inline bool isCurrentWindowClosed() { return glfwWindowShouldClose(glfwGetCurrentContext()) == 1; }

			/* Setters */
			void SetWindowHint(int hint, int value);
			void SetVSync(bool enabled);
			void SetWindowDimensions(int width, int height);
			void SetTitle(const char* title);
			void SetInputMode(int mode, int value);

		private:
			static bool s_initialized;
	};
}}
