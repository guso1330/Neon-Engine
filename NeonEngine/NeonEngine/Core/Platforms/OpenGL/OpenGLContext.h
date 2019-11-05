#pragma once

#include "Core/Core.h"
#include "Graphics/Renderers/IGraphicContext.h"
#include "Graphics/Renderers/IRendererAPI.h"
#include "Core/Platforms/OpenGL/GL_Error.h"
#include "Core/Platforms/OpenGL/VertexBuffer.h"
#include "Core/Platforms/OpenGL/VertexArray.h"
#include "Core/Platforms/OpenGL/IndexBuffer.h"
#include "Core/Platforms/OpenGL/uniformBuffer.h"
#include "Core/Platforms/OpenGL/Shader.h"
#include "Core/Platforms/OpenGL/Program.h"
#include "Core/Platforms/OpenGL/Texture.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

namespace Neon { namespace OpenGL {
	class OpenGLContext :
		public IGraphicContext,
		public IRendererAPI
	{
		typedef std::unordered_map<unsigned int, std::shared_ptr<VertexArray> > VertexArrayMap;
		typedef std::unordered_map<unsigned int, UniformBuffer*> UniformBufferMap;
		typedef std::unordered_map<unsigned int, std::shared_ptr<Shader> > ShaderMap;
		typedef std::unordered_map<unsigned int, std::shared_ptr<Program> > ProgramMap;
		typedef std::unordered_map<unsigned int, std::shared_ptr<Texture> > TextureMap;

		public:
			/* Constructors */
			OpenGLContext(OpenGLContext const&) = delete;
			
			/* Operator Overrides */
			void operator=(OpenGLContext const&) = delete;

			/* Methods */
			virtual void Clear() override;
			virtual void DrawIndexed(const std::shared_ptr<IVertexArray>& vao) override;
			void DrawIndexed(const unsigned int vao_id, unsigned int num_elements, unsigned int draw_mode);
			void UpdateUbo(unsigned int ubo_id, const void* data, size_t data_size);

			/* Create methods */
			void CreateContext() override;
			std::shared_ptr<VertexArray> CreateVao(const void* data, size_t data_size, const unsigned int* indices, unsigned int indices_count, const BufferLayout& layout, BufferUsage usage);
			std::shared_ptr<Shader> CreateShader(const std::string& filename, const ShaderType shader_type);
			std::shared_ptr<Program> CreateProgram(const std::string name, std::shared_ptr<Shader>& vertexShader, std::shared_ptr<Shader>& fragmentShader);
			std::shared_ptr<Texture> CreateTexture(const std::string& filename, TextureType type);
			unsigned int CreateUniformBuffer(const void* data, size_t data_size, BufferUsage usage);

			/* Binding Methods */
			void BindTexture(unsigned int tex_id, unsigned int unit);
			void BindVao(unsigned int vao_id);
			void BindProgram(unsigned int program_id);

			/* Getters */
			static OpenGLContext& GetInstance();
			inline std::shared_ptr<Program>& GetProgram(unsigned int program_id) { return m_programMap[program_id]; }
			void GetActiveUniforms();
			void GetActiveAttributes();

			/* Setters */
			virtual void SetClearColor(float r, float g, float b, float a) override;

		public:
			static unsigned int GL_BufferUsage(BufferUsage usage);

		/* Private Methods */
		private:
			OpenGLContext() {}
			bool Init();

		/* Private Variables */
		private:
			static bool s_initialized;
			glm::vec4 m_clearColor;
			unsigned int m_currentVao;
			unsigned int m_currentProgram;

		/* Private Structures/Containers */
		private:
			VertexArrayMap m_vaoMap;
			ShaderMap m_shaderMap;
			ProgramMap m_programMap;
			TextureMap m_textureMap;
			UniformBufferMap m_uniformBufferMap;
	};
}}
