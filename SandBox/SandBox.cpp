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
		ExampleLayer() : Layer("Example") {
			// Initialize the camera
			float aspect_ratio = (float)WIDTH / (float)HEIGHT;
			float fov = 70.0f;
			float near = 0.01f;
			float far = 1000.0f;
			m_Camera = new Neon::Camera(glm::vec3(0.0f, 0.0f, -5.0f), fov, aspect_ratio, near, far);
		}

		~ExampleLayer() {
			delete m_Camera;
		}

		/* Getter Functions */
		inline Neon::Camera* GetCamera() const { return m_Camera; }

		/* Member Functions */
		void OnAttach() override {
			srand(time(NULL));

			/* ECS Testing - BEGIN */
			size_t amount = 5000;
			Neon::Timer timer;
			Neon::Timestep initialTime;
			Neon::ECS::EntityID e0;
			CameraComponent* camComponent;
			TransformComponent* tComp;

			timer.Init();
			initialTime = timer.GetTime();

			e0 = Neon::ECS::ECSManager::GetInstance().CreateEntity();
			camComponent = Neon::ECS::ECSManager::GetInstance().CreateComponent<CameraComponent>(e0, static_cast<void*>(new CameraData()));
			tComp = Neon::ECS::ECSManager::GetInstance().CreateComponent<TransformComponent>(e0, static_cast<void*>(new TransformData()));
			Neon::ECS::ECSManager::GetInstance().CreateSystem<CameraSystem>();

			tComp->transformData->transform.SetPosition(glm::vec3(0.0, 0.0, -5.0));

			NE_WARN("EntityPool used memory used: {}", Neon::ECS::ECSMemory::EntityPool.GetUsedMemory());
			NE_WARN("ComponentPool used memory used: {}", Neon::ECS::ECSMemory::EntityPool.GetUsedMemory());
			NE_WARN("EntityPool Alloc Test: New/Delete total time - {}\n", timer.GetTime() - initialTime);
			/* ECS Testing - END */

			Neon::BufferLayout model_layout = {
				{ "vPosition", Neon::ShaderDataType::FLOAT3 },
				{ "vTexCoord", Neon::ShaderDataType::FLOAT2 },
				{ "vNormal", Neon::ShaderDataType::FLOAT3 }
			};

			// Load all Models
			Neon::Model Cube("res/models/cube_basic.obj");
			Neon::Model m9("res/models/m9.obj");
			
			std::vector<Neon::Mesh*> meshes;
			meshes.reserve(Cube.GetMeshes().size() + m9.GetMeshes().size());
			meshes.insert(meshes.end(), Cube.GetMeshes().begin(), Cube.GetMeshes().end());
			meshes.insert(meshes.end(), m9.GetMeshes().begin(), m9.GetMeshes().end());

			for(std::vector<Neon::Mesh*>::iterator it=meshes.begin(); it != meshes.end(); ++it) {
				std::vector<Neon::Vertex> c_verts = (*it)->GetVertexData();
				std::vector<unsigned int> c_inds = (*it)->GetIndices();
				std::shared_ptr<Neon::IVertexArray> n_vao;
				std::shared_ptr<Neon::IVertexBuffer> n_vbo;
				std::shared_ptr<Neon::IIndexBuffer> n_ibo;

				n_vao = std::shared_ptr<Neon::IVertexArray>(Neon::IVertexArray::Create());
				n_vao->Bind();

				n_vbo = std::shared_ptr<Neon::IVertexBuffer>(Neon::IVertexBuffer::Create(
					&c_verts.front(),
					c_verts.size() * sizeof(Neon::Vertex),
					model_layout
				));

				n_ibo = std::shared_ptr<Neon::IIndexBuffer>(Neon::IIndexBuffer::Create(
					&c_inds.front(),
					c_inds.size()
				));

				n_vao->AttachVertexBuffer(n_vbo);
				n_vao->AttachIndexBuffer(n_ibo);

				m_vaos.push_back(n_vao);
			}

			/* Create the shaders and the program */
			m_Texture = std::shared_ptr<Neon::ITexture>(Neon::ITexture::Create(
				"res/textures/checkered_colored.jpg",
				Neon::TextureType::DIFFUSE
			));
			m_Texture->Bind();

			m_Program = std::shared_ptr<Neon::IProgram>(Neon::IProgram::Create(
				"textureShaderProgram",
				"res/shaders/textureVShader.glsl",
				"res/shaders/textureFShader.glsl"
			));
		}

		void OnUpdate(Neon::Timestep ts) override {
			float angle;
			float speed;
			Neon::RenderMatrices mats;
			Neon::Camera* camera;
			CameraComponent* cameraComponent;

			Neon::Renderer::GetInstance().Clear();
			cameraComponent = Neon::ECS::ECSManager::GetInstance().GetComponent<CameraComponent>(0);
			camera = cameraComponent->cameraData->camera;

			// Set Up simple program
			angle = 0.0f;
			speed = 1.0f;
			angle += (ts * speed);
			if (angle > 360.0) {
				angle = 0;
			}
			m_modelMatrix = m_modelMatrix * glm::rotate(angle, glm::vec3(0.0, 1.0f, 0.0));
			mats.viewProjection = camera->GetViewProjection();

			int i = 0;
			for(std::vector<std::shared_ptr<Neon::IVertexArray> >::iterator it = m_vaos.begin(); it != m_vaos.end(); ++it) {
				mats.transform = glm::translate(m_modelMatrix, glm::vec3(0.0, 0.0, (float)2.0f * i));
				Neon::Renderer::GetInstance().Submit((*it), m_Program, mats);
				++i;
			}
		}

	private:
		glm::mat4 m_modelMatrix = glm::mat4(1.0f);
		Neon::Camera* m_Camera;
		std::shared_ptr<Neon::IProgram> m_Program;
		std::shared_ptr<Neon::ITexture> m_Texture;
		std::vector<std::shared_ptr<Neon::IVertexArray> > m_vaos;
};

class SandBox : public Neon::Application {
	public:
		SandBox(const Neon::WindowSettings &settings) :
			Neon::Application(settings)
		{}

		bool Init() override {
			NE_INFO("SandBox: SandBox app initialized");

			// Create window
			Neon::IWindow* window = this->GetWindow();
			glfwSetCursorPos(static_cast<GLFWwindow*>(window->GetNativeWindow()), WIDTH/2, HEIGHT/2);

			// Create a render layer
			m_exampleLayer = new ExampleLayer();
			PushLayer(m_exampleLayer);

			// Initialize Application Events
			float camera_rotate_speed = static_cast<float>((M_PI / 180.0f) * 0.1);

			Neon::EventManager::GetInstance().AddEventHandler(NEON_EVENT_KEY_PRESS, Neon::KeyPressCallback(
				[this](int key, int action, int mods) {
					if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
						NE_WARN("SandBox: Closing application window");
						this->GetWindow()->Close();
					}
				}
			));

			Neon::EventManager::GetInstance().AddEventHandler(NEON_EVENT_MOUSE_CURSOR, Neon::MouseCursorCallback(
				[this, window, camera_rotate_speed]
				(int x, int y) {
					MoveCameraAroundFunc(
						window,
						m_exampleLayer->GetCamera(),
						x,
						y,
						camera_rotate_speed
					);
				}
			));

			glfwSetInputMode(static_cast<GLFWwindow*>(window->GetNativeWindow()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

			return true;
		}

		~SandBox() = default;

		void Update(Neon::Timestep ts) override {
			float update_ts = (60.0f * ts) / 1000.0f; // TODO: divide by 60.0f?
			float camera_velocity = 0.3f;
			float camera_speed_limit = 2.0f;

			Neon::Debug::CalcFPS(this->GetWindow(), 1.0, "Neon Engine");

			MoveCameraFunc(
				m_exampleLayer->GetCamera(),
				(this->GetWindow())->GetInput(),
				m_cameraSpeed,
				camera_velocity,
				camera_speed_limit,
				update_ts
			);

			// Disable the cursor
			glfwSetCursorPos(static_cast<GLFWwindow*>(this->GetWindow()->GetNativeWindow()), WIDTH/2, HEIGHT/2);
		}

	private:
		float m_cameraSpeed = 0.0f;
		ExampleLayer* m_exampleLayer;
};

Neon::Application* Neon::CreateApplication() {
	Neon::WindowSettings windowSettings;
	windowSettings.width = WIDTH;
	windowSettings.height = HEIGHT;
	windowSettings.title = "Neon Engine";

	return new SandBox(windowSettings);
}
