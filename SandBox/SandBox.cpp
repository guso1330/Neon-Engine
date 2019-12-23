#include "NeonEngine/NeonEngine.h"

#include "nepch.h"

const int WIDTH = 512,
		  HEIGHT = 256;

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

Neon::Memory::LinearAllocator LAllocator;
Neon::Memory::PoolAllocator PAllocator;

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

		/* Getter Functions */
		inline Neon::Camera* GetCamera() const { return m_Camera; }

		/* Member Functions */
		void OnAttach() override {
			srand(time(NULL));

			/*
				Memory testing - BEGIN
			*/
			struct Complex {
				void* operator new (size_t alloc_size) {
					void* return_address = LAllocator.Allocate(alloc_size);
					if (return_address == nullptr) {
						LAllocator.Clean();
						return_address = LAllocator.Allocate(alloc_size);
					}
					return return_address;
				}

				void operator delete (void* deletePtr) {}

				// std::unordered_map<int, std::vector<std::string>> umap;
				// std::map<int, std::string> map;
				// std::vector<int> list;
				// std::string s;
				// double d;
				// int a;
				// int b;
				char c;
				char d;
				char e;
			};
			NE_WARN("Complex has a sizeof({}) and an alignof({})", sizeof(Complex), alignof(Complex));
			Neon::Timer timer;
			Neon::Timestep initialTime;
			Complex* t[1000];

			LAllocator.Init(1048576);
			PAllocator.Init<Complex>(500);

			timer.Init();
			initialTime = timer.GetTime();

			for (int x=0; x < 5000; ++x) {

				// Run New test
				for (int i=0; i < 1000; ++i) {
					t[i] = new Complex();
				}

				// // Run Delete test
				// for (int j=0; j < 1000; ++j) {
				// 	delete t[j];
				// }

				LAllocator.Clean();
			}

			NE_WARN("Memory Alloc Test: New/Delete total time - {}\n", timer.GetTime() - initialTime);

			LAllocator.Clean();

			exit(EXIT_SUCCESS);
			/*
				Memory testing - END
			*/

			Neon::BufferLayout model_layout = {
				{ "vPosition", Neon::ShaderDataType::FLOAT3 },
				{ "vTexCoord", Neon::ShaderDataType::FLOAT2 },
				{ "vNormal", Neon::ShaderDataType::FLOAT3 }
			};

			// Load all Models
			Neon::Model Cube("./SandBox/res/models/cube_basic.obj");
			Neon::Model Suzanne("./SandBox/res/models/m9.obj");
			
			std::vector<Neon::Mesh*> meshes;
			meshes.reserve(Cube.GetMeshes().size() + Suzanne.GetMeshes().size());
			meshes.insert(meshes.end(), Cube.GetMeshes().begin(), Cube.GetMeshes().end());
			meshes.insert(meshes.end(), Suzanne.GetMeshes().begin(), Suzanne.GetMeshes().end());

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
				"./SandBox/res/textures/checkered_colored.jpg",
				Neon::TextureType::DIFFUSE
			));
			m_Texture->Bind();

			m_Program = std::shared_ptr<Neon::IProgram>(Neon::IProgram::Create(
				"textureShaderProgram",
				"./SandBox/res/shaders/textureVShader.glsl",
				"./SandBox/res/shaders/textureFShader.glsl"
			));
		}

		void OnUpdate(Neon::Timestep ts) override {
			float angle;
			float speed;
			Neon::RenderMatrices mats;

			Neon::Renderer::GetInstance().Clear();

			m_Camera->Update();

			// Set Up simple program
			angle = 0.0f;
			speed = 1.0f;
			angle += (ts * speed);
			if (angle > 360.0) {
				angle = 0;
			}
			m_modelMatrix = m_modelMatrix * glm::rotate(angle, glm::vec3(0.0, 1.0f, 0.0));
			mats.viewProjection = m_Camera->GetViewProjection();

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
		SandBox() {}

		SandBox(const Neon::WindowSettings &settings) :
			Neon::Application(settings)
		{
			NE_INFO("SandBox: SandBox app initialized");

			// Create window
			Neon::IWindow* window = this->GetWindow();
			glfwSetCursorPos(static_cast<GLFWwindow*>(window->GetNativeWindow()), WIDTH/2, HEIGHT/2);

			// Create a render layer
			m_exampleLayer = new ExampleLayer();
			PushLayer(m_exampleLayer);

			// Initialize Application Events
			float camera_rotate_speed = (M_PI / 180.0f) * 0.1;

			Neon::EventManager::AddEventHandler(NEON_EVENT_KEY_PRESS, Neon::KeyPressCallback(
				[this](int key, int action, int mods) {
					if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
						NE_WARN("SandBox: Closing application window");
						this->GetWindow()->Close();
					}
				}
			));

			Neon::EventManager::AddEventHandler(NEON_EVENT_MOUSE_CURSOR, Neon::MouseCursorCallback(
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
		}

		void Update(Neon::Timestep ts) override {
			float update_ts = (60.0f * ts) / 1000.0f; // TODO: divide by 60.0f?
			float camera_velocity = 0.3f;
			float camera_speed_limit = 2.0f;

			Neon::Debug::CalcFPS(this->GetWindow(), 1.0, "Neon Engine");

			MoveCameraFunc(
				m_exampleLayer->GetCamera(),
				(dynamic_cast<Neon::MacOSWindow*>(this->GetWindow()))->GetInput(),
				m_cameraSpeed,
				camera_velocity,
				camera_speed_limit,
				update_ts
			);

			// Disable the cursor
			glfwSetCursorPos(static_cast<GLFWwindow*>(this->GetWindow()->GetNativeWindow()), WIDTH/2, HEIGHT/2);
		}

		~SandBox() {}

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
