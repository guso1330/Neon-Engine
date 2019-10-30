#include "NeonEngine/NeonEngine.h"

#include <unistd.h>

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

class ExampleLayer : public Neon::Layer {
	public:
		ExampleLayer() : Layer("Example") {
			Neon::OpenGL::OpenGLContext::GetInstance().CreateContext();
			//
			// Initialize the camera
			//
			float aspect_ratio = (float)WIDTH / (float)HEIGHT;
			float fov = 70.0f;
			float near = 0.01f;
			float far = 1000.0f;
			m_Camera = new Neon::Camera(glm::vec3(0.0f, 0.0f, -5.0f), fov, aspect_ratio, near, far);
		}

		/* Getter Functions */
		inline Neon::Camera* GetCamera() const { return m_Camera; }

		void OnAttach() override {
			srand(time(NULL));

			Neon::BufferLayout model_layout = {
				{ "vPosition", Neon::ShaderDataType::FLOAT3 },
				{ "vTexCoord", Neon::ShaderDataType::FLOAT2 },
				{ "vNormal", Neon::ShaderDataType::FLOAT3 }
			};

			Neon::Model model("./SandBox/res/models/cube_basic.obj");
			std::vector<Neon::Mesh*> meshes = model.GetMeshes();

			for(std::vector<Neon::Mesh*>::iterator it=meshes.begin(); it != meshes.end(); ++it) {
				std::vector<Neon::Vertex> c_verts = (*it)->GetVertexData();
				std::vector<unsigned int> c_inds = (*it)->GetIndices();

				unsigned int c_vao = Neon::OpenGL::OpenGLContext::GetInstance().CreateVao(
					&c_verts.front(),
					c_verts.size() * sizeof(Neon::Vertex),
					&c_inds.front(),
					c_inds.size(),
					model_layout,
					Neon::BufferUsage::STATIC
				);

				m_vaos.insert(std::make_pair(c_vao, std::make_pair(c_vao, (*it)->GetIndicesSize())));
			}

			/* Create the shaders and the program */
			const unsigned int shaders[2] = {
				Neon::OpenGL::OpenGLContext::GetInstance().CreateShader("./SandBox/res/shaders/textureVShader.glsl", GL_VERTEX_SHADER),
				Neon::OpenGL::OpenGLContext::GetInstance().CreateShader("./SandBox/res/shaders/textureFShader.glsl", GL_FRAGMENT_SHADER)
			};

			const char* texture_file_path = "./SandBox/res/textures/checkered_colored.jpg";
			const unsigned int texture_id = Neon::OpenGL::OpenGLContext::GetInstance().CreateTexture(texture_file_path, Neon::Diffuse, 0);

			unsigned int program_id = Neon::OpenGL::OpenGLContext::GetInstance().CreateProgram(shaders, 2);
			Neon::OpenGL::OpenGLContext::GetInstance().BindProgram(program_id);
			m_Program = Neon::OpenGL::OpenGLContext::GetInstance().GetProgram(program_id);

			// TODO: Needs to be manually set at the moment...
			m_Program->SetUniform4f("vcolor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		}

		void OnUpdate(Neon::Timestep ts) override {
			float angle;
			float speed;

			Neon::OpenGL::OpenGLContext::GetInstance().Clear();

			m_Camera->Update();

			// Set Up simple program
			angle = 0.0f;
			speed = 1.0f;
			angle += (ts * speed);
			if (angle > 360.0) {
				angle = 0;
			}
			m_modelMatrix = m_modelMatrix * glm::rotate(angle, glm::vec3(0.0, 1.0f, 0.0));
			m_Program->SetUniformMat4("model", m_modelMatrix);
			m_Program->SetUniformMat4("matrices.view_projection", m_Camera->GetViewProjection());

			for(int i=0; i < m_vaos.size(); ++i)
				Neon::OpenGL::OpenGLContext::GetInstance().DrawIndexed(m_vaos[i].first, m_vaos[i].second, GL_TRIANGLES);
		}
	private:
		glm::mat4 m_modelMatrix = glm::mat4(1.0f);
		Neon::Camera* m_Camera;
		Neon::Program* m_Program;
		std::map<unsigned int, std::pair<unsigned int, unsigned int> > m_vaos;
};

class SandBox : public Neon::Application {
	public:
		SandBox() {}

		SandBox(const Neon::WindowSettings &settings) :
			Neon::Application(settings)
		{
			NE_INFO("SandBox: SandBox app initialized");

			Neon::IWindow* window = this->GetWindow();
			glfwSetCursorPos(static_cast<GLFWwindow*>(window->GetNativeWindow()), WIDTH/2, HEIGHT/2);

			m_exampleLayer = new ExampleLayer();
			PushLayer(m_exampleLayer);

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

			// Disable the cursor
			glfwSetCursorPos(static_cast<GLFWwindow*>(window->GetNativeWindow()), WIDTH/2, HEIGHT/2);
			glfwSetInputMode(static_cast<GLFWwindow*>(window->GetNativeWindow()), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}

		void Update(Neon::Timestep ts) override {
			float update_ts = (60.0f * ts) / 1000.0f; // TODO: divide by 60.0f?
			float camera_velocity = 0.3f;
			float camera_speed_limit = 2.0f;

			MoveCameraFunc(
				m_exampleLayer->GetCamera(),
				(dynamic_cast<Neon::MacOSWindow*>(this->GetWindow()))->GetInput(),
				m_cameraSpeed,
				camera_velocity,
				camera_speed_limit,
				update_ts
			);
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
