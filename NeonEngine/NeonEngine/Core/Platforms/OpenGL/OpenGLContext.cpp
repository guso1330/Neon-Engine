#include "Core/Platforms/OpenGL/OpenGLContext.h"

#include "nepch.h"

namespace Neon { namespace OpenGL {
	bool OpenGLContext::s_initialized = false;

	void OpenGLContext::CreateContext() {
		if(!s_initialized && Init()) {
			s_initialized = true;

			/* Print Renderer and OpenGL info */
			const GLubyte *renderer = glGetString(GL_RENDERER);
			const GLubyte *version = glGetString(GL_VERSION);
			NE_CORE_INFO("OpenGLContext: Renderer - {}", renderer);
			NE_CORE_INFO("OpenGLContext: OpenGL Version - {}", version);
		}
	}

	bool OpenGLContext::Init() {
		// Setting up glad and initializing it
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			NE_CORE_ASSERT(false, "Failed to initialize GLAD");
			return false;
		}

		// Set all default values
		m_clearColor = glm::vec4(50.0f/255.0f, 78.0f/255.0f, 119.0f/255.0f, 1);
		GL_Call(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w));
		m_currentProgram = 0;

		// OpenGL Setting
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_CULL_FACE);
		glClearDepth(1.0f);

		return true;
	}

	void OpenGLContext::DrawIndexed(const std::shared_ptr<IVertexArray>& vao) {
		GL_Call(glDrawElements(GL_TRIANGLES, vao->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, NULL));
	}

	void OpenGLContext::DrawIndexed(const unsigned int vao_id, unsigned int num_elements, unsigned int draw_mode) {
		// Grab the vao from the vaoMap
		VertexArrayMap::const_iterator vao_it = m_vaoMap.find(vao_id);

		BindProgram(m_currentProgram);

		if(vao_it != m_vaoMap.end()) {
			(*vao_it).second->Bind();

			GL_Call(glDrawElements(draw_mode, num_elements, GL_UNSIGNED_INT, NULL));
		}
	}

	void OpenGLContext::Clear() {
		GL_Call(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		GL_Call(glFlush());
	}

	/********************/
	/* CREATE FUNCTIONS */
	/********************/
	// Note: For now this function will support one VBO and one IBO per VAO. This is to ensure that 
	//		 it stays as simple as possible until necessary
	std::shared_ptr<VertexArray> OpenGLContext::CreateVao(const void* data, size_t data_size, const unsigned int* indices, unsigned int indices_count, const BufferLayout& layout, BufferUsage usage) {

		// OpenGL Structures
		std::shared_ptr<VertexArray> vao = std::make_shared<VertexArray>();
		std::shared_ptr<VertexBuffer> vbo = std::make_shared<VertexBuffer>(usage);
		std::shared_ptr<IndexBuffer> ibo = std::make_shared<IndexBuffer>();

		// Bind the VAO, VBO, IBO
		vao->Bind();

		vbo->Bind();
		vbo->SetBufferData(data, data_size);
		vbo->SetLayout(layout);

		ibo->Bind();
		ibo->SetBufferData(indices, indices_count);

		vao->AttachVertexBuffer(vbo);
		vao->AttachIndexBuffer(ibo);

		vao->Unbind();

		// Handle VAO ID
		m_vaoMap.insert(std::make_pair(vao->GetVao(), vao));
		m_currentVao = vao->GetVao();

		return vao;
	}

	std::shared_ptr<Shader> OpenGLContext::CreateShader(const std::string& filename, const ShaderType shader_type) {
		std::shared_ptr<Shader> shader = std::make_shared<Shader>(filename.c_str(), shader_type);
		
		m_shaderMap.insert(std::make_pair(shader->GetId(), shader));

		return shader;
	}

	/* TODO: This API is some what weird. Why input an array and require the size to be passed in? Is this necessary or could it be simplified? */
	std::shared_ptr<Program> OpenGLContext::CreateProgram(const std::string name, std::shared_ptr<Shader>& vertexShader, std::shared_ptr<Shader>& fragmentShader) {
		std::shared_ptr<Program> program = std::make_shared<Program>(name, vertexShader, fragmentShader);
		unsigned int program_id = program->GetId();

		m_programMap.insert(std::make_pair(program_id, program));

		return program;
	}

	std::shared_ptr<Texture> OpenGLContext::CreateTexture(const std::string& filename, TextureType type) {
		std::shared_ptr<Texture> texture = std::make_shared<Texture>(filename, type);
		m_textureMap.insert(std::make_pair(texture->GetId(), texture));

		return texture;
	}

	unsigned int OpenGLContext::CreateUniformBuffer(const void* data, size_t data_size, BufferUsage usage) {
		UniformBuffer* ubo = new UniformBuffer();
		unsigned int ubo_id = ubo->GetUbo();

		m_uniformBufferMap.insert(std::make_pair(ubo_id, ubo));

		return ubo_id;
	}

	/******************/
	/* Bind Functions */
	/******************/
	void OpenGLContext::BindTexture(unsigned int tex_id, unsigned int unit) {
		TextureMap::iterator texture_it = m_textureMap.find(tex_id);
		if(texture_it != m_textureMap.end()) {
			(*texture_it).second->Bind(unit);
		}
	}

	void OpenGLContext::BindVao(unsigned int vao_id) {
		if(vao_id == m_currentVao) {
			return;
		}

		VertexArrayMap::iterator vao_it = m_vaoMap.find(vao_id);
		if(vao_it != m_vaoMap.end()) {
			m_currentVao = vao_id;
			(*vao_it).second->Bind();
		}
	}

	void OpenGLContext::BindProgram(unsigned int program_id) {
		if(program_id == m_currentProgram) {
			return;
		}
		
		// Check if the program exists
		ProgramMap::iterator program_it = m_programMap.find(program_id);
		if(program_it != m_programMap.end()) {
			m_currentProgram = program_id;
			(*program_it).second->Bind(); // Bind the program
			NE_CORE_INFO("OpenGL: Program {} was bound", program_id);
			return;
		}

		NE_CORE_WARN("OpenGL: Program {} could not be bound");
	}

	/*****************/
	/* GET FUNCTIONS */
	/*****************/
	OpenGLContext& OpenGLContext::GetInstance() {
		static OpenGLContext instance;
		return instance;
	}

	void OpenGLContext::GetActiveAttributes() {
		int i;
		int count;

		int size; // size of the variable
		GLenum type; // type of the variable (float, vec3 or mat4, etc)

		const int bufSize = 16; // maximum name length
		char name[bufSize]; // variable name in GLSL
		int length; // name length

		GL_Call(glGetProgramiv(m_currentProgram, GL_ACTIVE_ATTRIBUTES, &count));
		NE_CORE_INFO("OpenGLContext: Active Attributes: {}", count);

		for (i = 0; i < count; i++)
		{
			glGetActiveAttrib(m_currentProgram, (unsigned int)i, bufSize, &length, &size, &type, name);
			NE_CORE_INFO("OpenGLContext: Attribute #{} Type: {} Name: {}", i, type, name);
		}
	}

	void OpenGLContext::GetActiveUniforms() {
		int num_block;

		GL_Call(glGetProgramiv(m_currentProgram, GL_ACTIVE_UNIFORM_BLOCKS, &num_block));

		std::shared_ptr<Program> current_program = GetProgram(m_currentProgram);

		// Get and save the Uniform Blocks
		for(int block = 0; block < num_block; ++block) {
			int name_len;

			// Get name length
			GL_Call(glGetActiveUniformBlockiv(current_program->GetId(), block, GL_UNIFORM_BLOCK_NAME_LENGTH, &name_len));

			// Get name
			char* name;
			GL_Call(glGetActiveUniformBlockName(current_program->GetId(), block, name_len, NULL, &name[0]));
			std::string uniform_block_name((char*)&name[0], name_len-1);
			
			// Save name to the uniformMap
			unsigned int block_index = glGetUniformBlockIndex(current_program->GetId(), &name[0]);
			// TODO: Implement this save uniform function
			// current_program->SaveUniform(block_index, uniform_block_name);

			NE_CORE_INFO("OpenGLContext: uniformBlock {}: at {}", uniform_block_name, block_index);
		}

		// Get and save the Uniform Variables
		int count;

		int size; // size of the variable
		GLenum type; // type of the variable (float, vec3 or mat4, etc)

		const int bufSize = 16; // maximum name length
		char name[bufSize]; // variable name in GLSL
		int length; // name length

		GL_Call(glGetProgramiv(m_currentProgram, GL_ACTIVE_UNIFORMS, &count));
		NE_CORE_INFO("OpenGLContext: Active Uniforms {}", count);

		for (int i = 0; i < count; i++)
		{
			GL_Call(glGetActiveUniform(m_currentProgram, (unsigned int)i, bufSize, &length, &size, &type, name));
			NE_CORE_INFO("OpenGLContext: Uniform #{} Type: {} Name: {}", i, type, name);
		}
	}

	void OpenGLContext::UpdateUbo(unsigned int ubo_id, const void* data, size_t data_size) {
		UniformBufferMap::iterator ubo_it = m_uniformBufferMap.find(ubo_id);
		if(ubo_it != m_uniformBufferMap.end()) {
			(*ubo_it).second->Bind();
			void* dest = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
			memcpy(dest, data, data_size);
			(*ubo_it).second->Unbind();
		}
	}

	/*****************/
	/* SET FUNCTIONS */
	/*****************/
	void OpenGLContext::SetClearColor(float r, float g, float b, float a) {
		m_clearColor.x = r;
		m_clearColor.y = g;
		m_clearColor.z = b;
		m_clearColor.w = a;
		GL_Call(glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, m_clearColor.w));
	}
}}
