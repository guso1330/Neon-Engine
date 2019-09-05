#pragma once

#include "./GL_Error.h"
#include "./vertexArray.h"
#include "./vertexBuffer.h"
#include "./indexBuffer.h"
#include "./uniformBuffer.h"
#include "./shader.h"
#include "./program.h"
#include "./texture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Neon {
	enum class BufferUsage
	{
		STATIC, DYNAMIC
	};


	class OpenGLContext {
		typedef std::unordered_map<unsigned int, VertexArray*> VertexArrayMap;
		typedef std::unordered_map<unsigned int, UniformBuffer*> UniformBufferMap;
		typedef std::unordered_map<unsigned int, Shader*> ShaderMap;
		typedef std::unordered_map<unsigned int, Program*> ProgramMap;
		typedef std::unordered_map<unsigned int, Texture*> TextureMap;

		public:
			// Constructor
			OpenGLContext() {};
			~OpenGLContext() {};

			//
			// Public Functional Methods
			//
			void Clear() const;
			static void Draw(unsigned int vao_id, unsigned int num_elements, unsigned int draw_mode);

			//
			// Create methods
			//
			static void CreateContext();
			static unsigned int CreateVao(const void* data, size_t data_size, const unsigned int* indices, unsigned int indices_count, BufferLayout layout, BufferUsage usage);
			static unsigned int CreateShader(const std::string& filename, unsigned int shader_type);
			static unsigned int CreateProgram(const unsigned int shader_ids[], unsigned int size);
			static unsigned int CreateTexture(const std::string& filename, TextureType type, unsigned int unit);
			static unsigned int CreateUniformBuffer(const void* data, size_t data_size, BufferUsage usage);

			//
			// Binding Methods
			//
			static void BindTexture(unsigned int tex_id, unsigned int unit);
			static void BindVao(unsigned int vao_id);
			static void BindProgram(unsigned int program_id);

			//
			// Get Program
			//
			inline Program* GetProgram(unsigned int program_id) { return s_programMap[program_id]; }

			//
			// Set Methods
			//
			static void SetClearColor(float r, float g, float b, float a);

			void GetActiveUniforms();
			void GetActiveAttributes() const;

			static void UpdateUbo(unsigned int ubo_id, const void* data, size_t data_size);

		//
		// Private Methods
		//
		private:
			static bool Init();

		//
		// Private Variables
		//
		private:
			static glm::vec4 s_clearColor;
			static unsigned int s_currentVao;
			static unsigned int s_currentProgram;

		// Private Structures/Containers
		private:
			static VertexArrayMap s_vaoMap;
			static ShaderMap s_shaderMap;
			static ProgramMap s_programMap;
			static TextureMap s_textureMap;
			static UniformBufferMap s_uniformBufferMap;
	};
}
