#include "nepch.h"
#include "../../Core.h"
#include "./opengl.h"

namespace Neon {
	
	static unsigned int GL_BufferUsage(BufferUsage usage);

	glm::vec4 OpenGLContext::s_clearColor;
	unsigned int OpenGLContext::s_currentVao;
	unsigned int OpenGLContext::s_currentProgram;
	OpenGLContext::VertexArrayMap OpenGLContext::s_vaoMap;
	OpenGLContext::ShaderMap OpenGLContext::s_shaderMap;
	OpenGLContext::ProgramMap OpenGLContext::s_programMap;
	OpenGLContext::TextureMap OpenGLContext::s_textureMap;
	OpenGLContext::UniformBufferMap OpenGLContext::s_uniformBufferMap;


	void OpenGLContext::CreateContext() {
		if(Init()) {
			/* Print Renderer and OpenGL info */
			const GLubyte *renderer = glGetString(GL_RENDERER);
			const GLubyte *version = glGetString(GL_VERSION);
			NE_CORE_INFO("Renderer: {}", renderer);
			NE_CORE_INFO("OpenGL Version: {}", version);
		}
	}

	bool OpenGLContext::Init() {
		// Setting up glad and initializing it
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			NE_CORE_ASSERT(false, "Failed to initialize GLAD");
			return false;
		}

		// Set all default values
		s_clearColor = glm::vec4(50.0f/255.0f, 78.0f/255.0f, 119.0f/255.0f, 1);
		GL_Call(glClearColor(s_clearColor.x, s_clearColor.y, s_clearColor.z, s_clearColor.w));
		s_currentProgram = 0;

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
		VertexArrayMap::iterator vao_it = s_vaoMap.find(vao_id);

		BindProgram(s_currentProgram);

		if(vao_it != s_vaoMap.end()) {
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
	// TODO: For now this function will support one VBO and one IBO per VAO. This is to ensure that 
	//		 it stays as simple as possible until necessary
	unsigned int OpenGLContext::CreateVao(const void* data, size_t data_size, const unsigned int* indices, unsigned int indices_count, BufferLayout layout, BufferUsage usage) {

		VertexArray* vao = new VertexArray();
		VertexBuffer* vbo = new VertexBuffer(GL_BufferUsage(usage));
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
		s_currentVao = vao_id;

		vao->Unbind();

		// Increment and Handle VAO ID
		s_vaoMap.insert(std::make_pair(vao_id, vao));

		return vao_id;
	}

	unsigned int OpenGLContext::CreateShader(const std::string& filename, unsigned int shader_type) {
		Shader* shader = new Shader(filename.c_str(), shader_type);
		unsigned int shader_id = shader->GetShaderId();
		
		s_shaderMap.insert(std::make_pair(shader_id, shader));

		return shader_id;
	}

	/* TODO: This API is some what weird. Why input an array and require the size to be passed in? Is this necessary or could it be simplified? */
	unsigned int OpenGLContext::CreateProgram(const unsigned int shader_ids[], unsigned int size) {
		std::vector<Shader*> shaders;
		for(int i=0; i < size; ++i) {
			shaders.push_back(s_shaderMap[shader_ids[i]]);
		}

		Program* program = new Program(shaders);
		unsigned int program_id = program->GetProgramId();

		s_programMap.insert(std::make_pair(program_id, program));

		return program_id;
	}

	unsigned int OpenGLContext::CreateTexture(const std::string& filename, TextureType type, unsigned int unit) {
		Texture* texture = new Texture(filename, type);

		texture->Bind(unit);
		s_textureMap.insert(std::make_pair(texture->GetId(), texture));

		return texture->GetId();
	}

	unsigned int OpenGLContext::CreateUniformBuffer(const void* data, size_t data_size, BufferUsage usage) {
		UniformBuffer* ubo = new UniformBuffer();
		unsigned int ubo_id = ubo->GetUbo();

		s_uniformBufferMap.insert(std::make_pair(ubo_id, ubo));

		return ubo_id;
	}

	/******************/
	/* Bind Functions */
	/******************/
	void OpenGLContext::BindTexture(unsigned int tex_id, unsigned int unit) {
		TextureMap::iterator texture_it = s_textureMap.find(tex_id);
		if(texture_it != s_textureMap.end()) {
			(*texture_it).second->Bind(unit);
		}
	}

	void OpenGLContext::BindVao(unsigned int vao_id) {
		if(vao_id == s_currentVao) {
			return;
		}

		VertexArrayMap::iterator vao_it = s_vaoMap.find(vao_id);
		if(vao_it != s_vaoMap.end()) {
			s_currentVao = vao_id;
			(*vao_it).second->Bind();
		}
	}

	void OpenGLContext::BindProgram(unsigned int program_id) {
		if(program_id == s_currentProgram) {
			return;
		}
		
		// Check if the program exists
		ProgramMap::iterator program_it = s_programMap.find(program_id);
		if(program_it != s_programMap.end()) {
			s_currentProgram = program_id;
			(*program_it).second->Bind(); // Bind the program
			NE_CORE_INFO("Program {} was bound", program_id);
			return;
		}

		NE_CORE_WARN("Program {} could not be bound");
	}

	/*****************/
	/* GET FUNCTIONS */
	/*****************/
	void OpenGLContext::GetActiveAttributes() {
		int i;
		int count;

		int size; // size of the variable
		GLenum type; // type of the variable (float, vec3 or mat4, etc)

		const int bufSize = 16; // maximum name length
		char name[bufSize]; // variable name in GLSL
		int length; // name length

		GL_Call(glGetProgramiv(s_currentProgram, GL_ACTIVE_ATTRIBUTES, &count));
		NE_CORE_INFO("Active Attributes: {}", count);

		for (i = 0; i < count; i++)
		{
			glGetActiveAttrib(s_currentProgram, (unsigned int)i, bufSize, &length, &size, &type, name);
			NE_CORE_INFO("Attribute #{} Type: {} Name: {}", i, type, name);
		}
	}

	void OpenGLContext::GetActiveUniforms() {
		int num_block;

		GL_Call(glGetProgramiv(s_currentProgram, GL_ACTIVE_UNIFORM_BLOCKS, &num_block));

		Program* current_program = GetProgram(s_currentProgram);

		// Get and save the Uniform Blocks
		for(int block = 0; block < num_block; ++block) {
			int name_len;

			// Get name length
			GL_Call(glGetActiveUniformBlockiv(current_program->GetProgramId(), block, GL_UNIFORM_BLOCK_NAME_LENGTH, &name_len));

			// Get name
			char name[name_len];
			GL_Call(glGetActiveUniformBlockName(current_program->GetProgramId(), block, name_len, NULL, &name[0]));
			std::string uniform_block_name((char*)&name[0], name_len-1);
			
			// Save name to the uniformMap
			unsigned int block_index = glGetUniformBlockIndex(current_program->GetProgramId(), &name[0]);
			current_program->SaveUniform(block_index, uniform_block_name);

			NE_CORE_INFO("uniformBlock {}: at {}", uniform_block_name, block_index);
		}

		// Get and save the Uniform Variables
		int count;

		int size; // size of the variable
		GLenum type; // type of the variable (float, vec3 or mat4, etc)

		const int bufSize = 16; // maximum name length
		char name[bufSize]; // variable name in GLSL
		int length; // name length

		GL_Call(glGetProgramiv(s_currentProgram, GL_ACTIVE_UNIFORMS, &count));
		NE_CORE_INFO("Active Uniforms {}", count);

		for (int i = 0; i < count; i++)
		{
			GL_Call(glGetActiveUniform(s_currentProgram, (unsigned int)i, bufSize, &length, &size, &type, name));
			NE_CORE_INFO("Uniform #{} Type: {} Name: {}", i, type, name);
		}
	}

	void OpenGLContext::UpdateUbo(unsigned int ubo_id, const void* data, size_t data_size) {
		UniformBufferMap::iterator ubo_it = s_uniformBufferMap.find(ubo_id);
		if(ubo_it != s_uniformBufferMap.end()) {
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
		s_clearColor.x = r;
		s_clearColor.y = g;
		s_clearColor.z = b;
		s_clearColor.w = a;
		GL_Call(glClearColor(s_clearColor.x, s_clearColor.y, s_clearColor.z, s_clearColor.w));
	}

	static unsigned int GL_BufferUsage(BufferUsage usage) {
		switch(usage) {
			case BufferUsage::STATIC:
				return GL_STATIC_DRAW;
			case BufferUsage::DYNAMIC:
				return GL_DYNAMIC_DRAW;
			default: break;
		}
		return 0;
	}	
}
