#include "ImGuiLayer.h"

#include "nepch.h"
#include "imgui.h"
#include "Core/Core.h"
#ifdef NE_PLATFORM_MACOS
	#include <examples/imgui_impl_opengl3.cpp>
	#include <examples/imgui_impl_glfw.cpp>
#elif defined(NE_PLATFORM_WIN64)
	#include <examples/imgui_impl_opengl3.cpp>
	#include <examples/imgui_impl_glfw.cpp>
#endif
#include "App/Application.h"

namespace Neon {
	ImGuiLayer::ImGuiLayer() :
		Layer("ImGuiLayer")
	{}

	void ImGuiLayer::OnAttach() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		Application& app = Application::GetInstance();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer bindings
		#ifdef NE_PLATFORM_MACOS
			GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow()->GetNativeWindow());
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
		#elif defined(NE_PLATFORM_WIN64)
			GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow()->GetNativeWindow());
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
		#else
			NE_CORE_ASSERT(false, "ImGuiLayer: Failed to initialize the ImGui instances");
		#endif
	}

	void ImGuiLayer::OnDetach() {
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin() {
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetInstance();
		std::function<void()> OpenGL_GLFW_InitFunc = [this, io]() {
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}
		};

		io.DisplaySize = ImVec2(app.GetInstance().GetWindow()->GetWidth(), app.GetInstance().GetWindow()->GetHeight());

		// Rendering
		ImGui::Render();
		#ifdef NE_PLATFORM_MACOS
			OpenGL_GLFW_InitFunc();
		#elif defined(NE_PLATFORM_WIN64)
			OpenGL_GLFW_InitFunc();
		#endif
	}
}
