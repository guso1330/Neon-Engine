#include "NeonEngine/NeonEngine.h"

#include "nepch.h"

const int WIDTH = 1278,
		  HEIGHT = 720;

#ifdef NE_PLATFORM_WIN64
	#undef near
	#undef far
#endif // NE_PLATFORM_WIN64


/* Input Callback Functions */
auto MoveCameraFunc = [](Neon::Camera* camera, Neon::Input* inputManager, float& camera_speed, float camera_velocity, float camera_speed_limit, float elapsed_time) {
	glm::vec3 position = camera->GetPosition();

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
		float lx = glm::sin(camera->GetYaw())*glm::cos(camera->GetPitch());
		float ly = glm::sin(camera->GetPitch());
		float lz = glm::cos(camera->GetYaw())*glm::cos(camera->GetPitch());

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
			position += glm::cross(camera->GetRelativeUp(), camera->GetDirection()) * camera_speed;
			
		} else {
			position += glm::cross(camera->GetRelativeUp(), camera->GetDirection()) * -camera_speed;
		}
	}

	camera->SetPosition(position);
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

/*
	ECS Components & System testing - BEGIN
*/
struct CameraData {
	Neon::Camera* camera;
	glm::vec3 pos = glm::vec3(0.0);
	float fov = 70.0f;
	float aspectRatio = (float)WIDTH / (float)HEIGHT;
	float near = 0.01f;
	float far = 1000.0f;
};

struct TransformData {
	Neon::Transform transform;
};

struct CameraComponent : public Neon::ECS::IComponent {
	virtual bool Init(void* n_data) override {
		cameraData = static_cast<CameraData*>(n_data);

		cameraData->camera = new Neon::Camera(
			cameraData->pos,
			cameraData->fov,
			cameraData->aspectRatio,
			cameraData->near,
			cameraData->far
		);

		return true;
	}

	CameraData* cameraData;
};

struct TransformComponent : public Neon::ECS::IComponent {
	virtual bool Init(void* n_data) override {
		transformData = static_cast<TransformData*>(n_data);
		return true;
	}

	TransformData* transformData;
};

class CameraSystem : public Neon::ECS::ISystem {
	public:
		virtual bool Init() override {
			return true;
		}

		virtual void Update(Neon::Timestep ts) override {
			CameraComponent* camera_component;
			TransformComponent* transform_component;
			Neon::EntityMap entities;

			entities = Neon::ECS::ECSManager::GetInstance().GetEntities();

			for (Neon::EntityMap::const_iterator it = entities.begin(); it != entities.end(); ++it) {
				camera_component = Neon::ECS::ECSManager::GetInstance().GetComponent<CameraComponent>((*it).first);
				transform_component = Neon::ECS::ECSManager::GetInstance().GetComponent<TransformComponent>((*it).first);

				camera_component->cameraData->camera->SetPosition(
					transform_component->transformData->transform.GetPosition()
				);
				camera_component->cameraData->camera->Update();
			}
		}
};
/*
	ECS Components & System testing - END
*/

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
				 0.5f,  0.5f, 0.0f,  // top right
				 0.5f, -0.5f, 0.0f,  // bottom right
				-0.5f, -0.5f, 0.0f,  // bottom left
				-0.5f,  0.5f, 0.0f   // top left 
			};
			unsigned int indices[] = {  // note that we start from 0!
				0, 1, 3, // first triangle
				1, 2, 3  // second triangle
			};
			Neon::BufferLayout layout_2d = {
				{ "vPosition", Neon::ShaderDataType::FLOAT3 }
			};
			std::shared_ptr<Neon::IVertexBuffer> n_vbo(Neon::IVertexBuffer::Create(
				&vertices[0],
				3 * 4 * sizeof(float),
				layout_2d
			));
			std::shared_ptr<Neon::IIndexBuffer> n_ibo(Neon::IIndexBuffer::Create(
				&indices[0],
				6
			));

			p_vao = Neon::IVertexArray::Create();
			p_vao->Bind();

			p_vao->AttachVertexBuffer(n_vbo);
			p_vao->AttachIndexBuffer(n_ibo);

			p_program = Neon::IProgram::Create(
				"2dProgram",
				"res/shaders/2dVShader.glsl",
				"res/shaders/2dFShader.glsl"
			);

			p_vao->Unbind();

			return true;
		}

		~SandBox() = default;

		void Update(Neon::Timestep ts) override {
			Neon::RenderMatrices mats;
			Neon::Renderer::GetInstance().Submit(p_vao, p_program, mats);
		}

	private:
		Neon::IVertexArray* p_vao;
		Neon::IProgram* p_program;
};

Neon::Application* Neon::CreateApplication() {
	Neon::WindowSettings windowSettings;
	windowSettings.width = WIDTH;
	windowSettings.height = HEIGHT;
	windowSettings.title = "Test game";

	return new SandBox(windowSettings);
}
