#include "NeonEngine/NeonEngine.h"

#include "nepch.h"

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
		float lx = glm::sin(camera.GetYaw())*glm::cos(camera.GetPitch());
		float ly = glm::sin(camera.GetPitch());
		float lz = glm::cos(camera.GetYaw())*glm::cos(camera.GetPitch());

		if(inputManager->IsKeyDown(GLFW_KEY_S)) {
			position.x = position.x + (-camera_speed*lx);
			position.y = position.y + (-camera_speed*ly);
			position.z = position.z + (-camera_speed*lz);
		} else {
			position.x = position.x + camera_speed*lx;
			position.y = position.y + camera_speed*ly;
			position.z = position.z + camera_speed*lz;
		}
	}

	if(inputManager->IsKeyDown(GLFW_KEY_A) || inputManager->IsKeyDown(GLFW_KEY_D)) {
		if(inputManager->IsKeyDown(GLFW_KEY_A)) {				
			position += glm::cross(camera.GetRelativeUp(), camera.GetDirection()) * camera_speed;
			
		} else {
			position += glm::cross(camera.GetRelativeUp(), camera.GetDirection()) * -camera_speed;
		}
	}

	camera.SetPosition(position);
};

auto MoveCameraAroundFunc = [](Neon::IWindow* window, Neon::Camera* camera, int x, int y, float camera_rotate_speed) {
	int dx = x - WIDTH/2,
		dy = y - HEIGHT/2;

	if(dx) { // get rotation in the x direction
		camera->RotateYaw(-camera_rotate_speed * dx);
	}
	if(dy) {
		camera->RotatePitch(-camera_rotate_speed * dy);
	}

	camera->Update();
	glfwSetCursorPos(static_cast<GLFWwindow*>(window->GetNativeWindow()), WIDTH/2, HEIGHT/2);
};

class ExampleLayer : public Neon::Layer {
	public:
		ExampleLayer() : Layer("Example") {}

		~ExampleLayer() {}

		/* Member Functions */
		void OnAttach() override {}

		void OnUpdate(Neon::Timestep ts) override {}

	private:
};

class SandBox : public Neon::Application {
	public:
		SandBox(const Neon::WindowSettings &settings) :
			Neon::Application(settings)
		{}

		bool Init() override {
			float vertices[] = {
				 1.0f,  1.0f, 0.0f,  // top right
				 1.0f, -1.0f, 0.0f,  // bottom right
				-1.0f, -1.0f, 0.0f,  // bottom left
				-1.0f,  1.0f, 0.0f   // top left
			};
			unsigned int indices[] = {  // note that we start from 0!
				0, 1, 3, // first triangle
				1, 2, 3  // second triangle
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
				6
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

			return true;
		}

		~SandBox() = default;

		void Update(Neon::Timestep ts) override {
			Neon::RenderMatrices mats;
			Neon::Debug::CalcFPS(this->GetWindow(), 1.0, "Neon Engine");

			MoveCameraFunc(
				m_camera,
				(this->GetWindow())->GetInput(),
				CAMERA_SPEED,
				-0.2f,
				5.0f,
				ts
			);

			m_camera.SetLookAt(glm::vec3(0.0f, 0.0f, 0.0f));

			mats.transform = glm::mat4(1.0f);
			mats.viewProjection = m_camera.GetViewProjection();

			p_program->Bind();
			p_program->SetMat4("model", mats.transform);
			p_program->SetMat4("matrices.view_projection", mats.viewProjection);
			p_program->Unbind();

			Neon::Renderer::GetInstance().Submit(p_vao, p_program, mats);
		}

	private:
		Neon::IVertexArray* p_vao;
		Neon::OpenGL::Program* p_program;
		Neon::Camera m_camera;
};

Neon::Application* Neon::CreateApplication() {
	Neon::WindowSettings windowSettings;
	windowSettings.width = WIDTH;
	windowSettings.height = HEIGHT;
	windowSettings.title = "Test game";

	return new SandBox(windowSettings);
}
