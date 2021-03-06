#include "NeonEngine/NeonEngine.h"
#include "EventSystem/EventSystem.h"

bool show_another_window = false;

#include "nepch.h"
#include "imgui.h"

int WIDTH = 1280,
	HEIGHT = 720;

float CAMERA_SPEED = 1.0f;

/* Input Callback Functions */
auto MoveCameraFunc = [](Neon::Camera& camera, Neon::Input* inputManager, float& camera_speed, float camera_velocity, float camera_speed_limit, float elapsed_time) {
	glm::vec3 position = camera.GetPosition();

	camera_speed = camera_speed + (camera_velocity * elapsed_time);

	// On Key up set camera_speed to 0
	if(inputManager->IsKeyUp(GLFW_KEY_A) &&
	   inputManager->IsKeyUp(GLFW_KEY_D) &&
	   inputManager->IsKeyUp(GLFW_KEY_W) &&
	   inputManager->IsKeyUp(GLFW_KEY_S)) {
		camera_speed = 0.0f;
	}

	// Limit Camera Speed
	if (camera_speed > camera_speed_limit) {
		camera_speed = camera_speed_limit;
	}

	if(inputManager->IsKeyDown(GLFW_KEY_W) || inputManager->IsKeyDown(GLFW_KEY_S)) {
		float lx = glm::cos(glm::radians(camera.GetYaw())) * glm::cos(glm::radians(camera.GetPitch()));
		float ly = glm::sin(glm::radians(camera.GetPitch()));
		float lz = glm::sin(glm::radians(camera.GetYaw())) * glm::cos(glm::radians(camera.GetPitch()));

		if(inputManager->IsKeyDown(GLFW_KEY_S)) {
			position.x = position.x + camera_speed * lx;
			position.y = position.y + camera_speed * ly;
			position.z = position.z + camera_speed * lz;
		} else {
			position.x = position.x + (-camera_speed * lx);
			position.y = position.y + (-camera_speed * ly);
			position.z = position.z + (-camera_speed * lz);
		}
	}

	if(inputManager->IsKeyDown(GLFW_KEY_A) || inputManager->IsKeyDown(GLFW_KEY_D)) {
		if(inputManager->IsKeyDown(GLFW_KEY_A)) {				
			position += glm::cross(camera.GetRelativeUp(), camera.GetDirection()) * -camera_speed;
			
		} else {
			position += glm::cross(camera.GetRelativeUp(), camera.GetDirection()) * camera_speed;
		}
	}

	camera.SetPosition(position);
};

auto MoveCameraAroundFunc = [](Neon::IWindow* window, Neon::Camera& camera, double x, double y, float sensitivity) {
	static bool isFirstMouseMove = true;
	static double lastX, lastY;
	float pitch;
	int dx, dy;

	glfwSetInputMode((GLFWwindow*)Neon::Application::GetInstance().GetWindow()->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (isFirstMouseMove) {
		lastX = x;
		lastY = y;
		isFirstMouseMove = false;
	}

	dx = x - lastX;
	dy = lastY - y;
	lastX = x;
	lastY = y;

	pitch = camera.GetPitch();

	if (pitch > 89.0f || pitch < -89.0f) {
		if(pitch > 89.0f)
			pitch = 89.0f;
		if(pitch < -89.0f)
			pitch = -89.0f;

		camera.SetPitch(pitch);
	} else {
		camera.RotatePitch(sensitivity * dy);
	}

	camera.RotateYaw(sensitivity * dx);
};

class RenderLayer : public Neon::Layer {
	public:
		RenderLayer() :
			Neon::Layer("RenderLayer")
		{}

		~RenderLayer() = default;

		virtual void OnAttach() override {
			float vertices[] = {
				// front
				-1.0, -1.0,  1.0,
				 1.0, -1.0,  1.0,
				 1.0,  1.0,  1.0,
				-1.0,  1.0,  1.0,
				// back
				-1.0, -1.0, -1.0,
				 1.0, -1.0, -1.0,
				 1.0,  1.0, -1.0,
				-1.0,  1.0, -1.0
			};
			unsigned int indices[] = {  // note that we start from 0!
				// front
				0, 1, 2,
				2, 3, 0,
				// right
				1, 5, 6,
				6, 2, 1,
				// back
				7, 6, 5,
				5, 4, 7,
				// left
				4, 0, 3,
				3, 7, 4,
				// bottom
				4, 5, 1,
				1, 0, 4,
				// top
				3, 2, 6,
				6, 7, 3
			};
			Neon::BufferLayout layout_2d = {
				{ "vPosition", Neon::ShaderDataType::FLOAT3 }
			};
			std::shared_ptr<Neon::IVertexBuffer> n_vbo;
			std::shared_ptr<Neon::IIndexBuffer> n_ibo;
			Neon::PerspectiveCameraSettings camSettings;

			p_vao = Neon::IVertexArray::Create();
			p_vao->Bind();
			n_vbo = std::shared_ptr<Neon::IVertexBuffer>(Neon::IVertexBuffer::Create(
				&vertices[0],
				sizeof(vertices),
				layout_2d
			));
			n_ibo = std::shared_ptr<Neon::IIndexBuffer>(Neon::IIndexBuffer::Create(
				&indices[0],
				6 * 6
			));

			p_vao->AttachVertexBuffer(n_vbo);
			p_vao->AttachIndexBuffer(n_ibo);

			p_program = (Neon::OpenGL::Program*)Neon::IProgram::Create(
				"2dProgram",
				"res/shaders/2dVShader.glsl",
				"res/shaders/2dFShader.glsl"
			);
			p_vao->Unbind();

			camSettings.position = glm::vec3(0.0f, 0.0f, 10.0f);
			camSettings.fov = 70.0f;
			camSettings.aspect = (float)WIDTH / (float)HEIGHT;
			camSettings.nearPlane = 0.01f;
			camSettings.farPlane = 1000.0f;
			m_camera.Init(camSettings);

			EventSystem::EventManager::GetInstance().AddEventListener<const Neon::KeyPressEvent&>(NEON_KEY_PRESS_EVENT, [this](const Neon::KeyPressEvent& event) {
				if (event.key == GLFW_KEY_ESCAPE) {
					Neon::Application::GetInstance().GetWindow()->Close();
				}
			});
		}

		virtual void OnUpdate(Neon::Timestep ts) override {
			Neon::RenderMatrices mats;

			MoveCameraAroundFunc(
				Neon::Application::GetInstance().GetWindow(),
				m_camera,
				(double)Neon::Application::GetInstance().GetWindow()->GetInput()->GetCursorPosition().x,
				(double)Neon::Application::GetInstance().GetWindow()->GetInput()->GetCursorPosition().y,
				0.1f
			);

			MoveCameraFunc(
				m_camera,
				(Neon::Application::GetInstance().GetWindow())->GetInput(),
				CAMERA_SPEED,
				-0.2f,
				5.0f,
				ts
			);

			m_camera.Update();

			mats.transform = glm::mat4(1.0f);
			mats.viewProjection = m_camera.GetViewProjection();

			p_program->Bind();
			p_program->SetMat4("model", mats.transform);
			p_program->SetMat4("matrices.view_projection", mats.viewProjection);
			p_program->Unbind();

			Neon::Renderer::GetInstance().Submit(p_vao, p_program, mats);
		}

		virtual void OnUpdateImGui(Neon::Timestep ts) override {
			static bool show = true;
			ImGui::ShowDemoWindow(&show);
		}

	private:
		Neon::IVertexArray* p_vao;
		Neon::OpenGL::Program* p_program;
		Neon::Camera m_camera;
};

class SandBox : public Neon::Application {
	public:
		SandBox(const Neon::WindowSettings &settings) :
			Neon::Application(settings)
		{}

		bool Init() override {
			PushLayer(new RenderLayer());

			return true;
		}

		~SandBox() = default;

		void Update(Neon::Timestep ts) override {
			Neon::Debug::CalcFPS(this->GetWindow(), 1.0, "Neon Engine");
		}

	private:

};

Neon::Application* Neon::CreateApplication() {
	Neon::WindowSettings windowSettings;
	windowSettings.width = WIDTH;
	windowSettings.height = HEIGHT;
	windowSettings.title = "Test game";

	return new SandBox(windowSettings);
}
