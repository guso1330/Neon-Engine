#include "ImGuiLayer.h"

#include "imgui.h"
#include "Core/Core.h"
#ifdef NE_PLATFORM_MACOS
	#include "Core/Platforms/GLFW/ImGuiGLFW.h"
	#include "Core/Platforms/OpenGL/ImGuiOpenGL.h"
#elif defined(NE_PLATFORM_WIN64)
	#include "Core/Platforms/GLFW/ImGuiGLFW.h"
	#include "Core/Platforms/OpenGL/ImGuiOpenGL.h"
#endif
#include "App/Application.h"

namespace Neon {
	ImGuiLayer::ImGuiLayer() :
		Layer("ImGuiLayer")
	{}

	ImGuiLayer::~ImGuiLayer() {
		// Cleanup
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnAttach() {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Setup Platform/Renderer bindings
		#ifdef NE_PLATFORM_MACOS
			ImGui_ImplOpenGL3_Init("#version 330");
		#elif defined(NE_PLATFORM_WIN64)
			ImGui_ImplOpenGL3_Init("#version 330");
		#else
			NE_CORE_ASSERT(false, "ImGuiLayer: Failed to initialize the ImGui instances");
		#endif
	}

	void ImGuiLayer::OnDetach() {}

	void ImGuiLayer::OnUpdate(Timestep ts) {
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::GetInstance();
		io.DisplaySize = ImVec2(app.GetInstance().GetWindow()->GetWidth(), app.GetInstance().GetWindow()->GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}
