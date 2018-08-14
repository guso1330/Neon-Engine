#include "./opengl.h"

namespace neon {

	OpenGLContext::OpenGLContext() {

		if(Init()) {
			/* Print Renderer and OpenGL info */
			const GLubyte *renderer = glGetString(GL_RENDERER);
			const GLubyte *version = glGetString(GL_VERSION);
			std::cout << "Neon Engine - Version 0.1" << std::endl;
			std::cout << "Renderer: " << renderer << std::endl;
			std::cout << "OpenGL Version: " << version << std::endl;
		}
	}

	bool OpenGLContext::Init() {
		// Setting up glad and initializing it
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cerr << "Failed to initialize GLAD" << std::endl;
			return false;
		}

		// Set all default values
		m_clearColor = glm::vec4(50.0f/255.0f, 78.0f/255.0f, 119.0f/255.0f, 1);
		GL_Call(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w));

		//
		// OpenGL Setting
		//
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_CULL_FACE);
		glClearDepth(1.0f);
		glEnable(GL_MULTISAMPLE);

		return true;
	}

	void OpenGLContext::Clear() const {
		GL_Call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_Call(glFlush());
	}

	// TODO: For now this function will support one VBO and one IBO per VAO. This is to ensure that 
	//		 it stays as simple as possible until necessary
	unsigned int OpenGLContext::CreateVao(const void* data, size_t data_size, const unsigned int* indices, unsigned int indices_count, BufferLayout layout, VertexBuffer::BufferUsage usage) {
		VertexArray* vao = new VertexArray();
		vao->Bind();
		VertexBuffer* vbo;
		IndexBuffer* ibo;

		vbo = new VertexBuffer(data, data_size, usage, layout);
		vao->PushBuffer(vbo);
		ibo = new IndexBuffer(indices, indices_count);

		unsigned int vao_id = vao->GetVao();

		// Increment and Handle VAO ID
		m_vaoMap.insert(std::pair<unsigned int, VertexArray*> (vao_id, vao));

		return vao_id;
	}

	void OpenGLContext::SetClearColor(float r, float g, float b, float a) {
		m_clearColor.x = r;
		m_clearColor.y = g;
		m_clearColor.z = b;
		m_clearColor.w = a;
		GL_Call(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w));
	}
}
