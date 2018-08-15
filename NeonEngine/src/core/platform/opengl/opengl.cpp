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
		m_currentProgram = NULL;

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

	void OpenGLContext::Draw(const unsigned int vao_id, unsigned int num_elements, unsigned int draw_mode) {

		// Grab the vao from the vaoMap
		VertexMap::iterator vao_it = m_vaoMap.find(vao_id);

		if(vao_it != m_vaoMap.end()) {
			VertexArray* vao = (*vao_it).second;
			vao->Bind();

			GL_Call(glDrawElements(draw_mode, num_elements, GL_UNSIGNED_INT, NULL));
		}

	}

	void OpenGLContext::Clear() const {
		GL_Call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_Call(glFlush());
	}

	// TODO: For now this function will support one VBO and one IBO per VAO. This is to ensure that 
	//		 it stays as simple as possible until necessary
	unsigned int OpenGLContext::CreateVao(const void* data, size_t data_size, const unsigned int* indices, unsigned int indices_count, BufferLayout layout, VertexBuffer::BufferUsage usage) {

		VertexArray* vao = new VertexArray();
		VertexBuffer* vbo = new VertexBuffer(usage);
		IndexBuffer* ibo = new IndexBuffer();
		unsigned int vao_id;

		// Bind the VAO, VBO, IBO
		vao->Bind();

		vbo->Bind();
		vbo->SetBufferData(data, data_size);
		vbo->SetLayout(layout);

		ibo->Bind();
		ibo->SetBufferData(indices, indices_count);

		vao_id = vao->GetVao();

		// Increment and Handle VAO ID
		m_vaoMap.insert(std::make_pair(vao_id, vao));

		return vao_id;
	}

	unsigned int OpenGLContext::CreateShader(const char* filename, unsigned int shaderType) {
		Shader* shader = new Shader(filename, shaderType);
		unsigned int shader_id = shader->GetShaderId();
		
		m_shaderMap.insert(std::make_pair(shader_id, shader));

		return shader_id;
	}

	unsigned int OpenGLContext::CreateProgram(const unsigned int shader_ids[], unsigned int size) {
		std::vector<Shader*> shaders;
		for(int i=0; i < size; ++i) {
			shaders.push_back(m_shaderMap[shader_ids[i]]);
		}


		Program* program = new Program(shaders);
		unsigned int program_id = program->GetProgramId();

		m_programMap.insert(std::make_pair(program_id, program));

		// Set the current program
		SetProgram(program_id);

		return program_id;
	}

	void OpenGLContext::SetClearColor(float r, float g, float b, float a) {
		m_clearColor.x = r;
		m_clearColor.y = g;
		m_clearColor.z = b;
		m_clearColor.w = a;
		GL_Call(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w));
	}

	void OpenGLContext::SetProgram(unsigned int program_id) {
		if(program_id == m_currentProgram) {
			return;
		}

		m_currentProgram = program_id;
		
		m_programMap[program_id]->Bind(); // Bind the program
	}
}
