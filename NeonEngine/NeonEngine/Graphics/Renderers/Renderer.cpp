#include "Graphics/Renderers/Renderer.h"

#include "nepch.h"

namespace Neon {
	bool Renderer::s_initialized = false;

	/* Static Functions defined */
	IVertexBuffer* IVertexBuffer::Create(void* data, size_t size, const BufferLayout& bufferLayout) {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
			 return new OpenGL::VertexBuffer(data, size, bufferLayout);
			case IRendererAPI::API::NONE: break;
			default: break;
		}
		NE_CORE_ASSERT(false, "IVertexBuffer Create: Undefined API");
		return 0;
	}

	IIndexBuffer* IIndexBuffer::Create(unsigned int* indices, size_t size) {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
				return new OpenGL::IndexBuffer(indices, size);
			case IRendererAPI::API::NONE: break;
			default: break;
		}
		NE_CORE_ASSERT(false, "IIndexBuffer Create: Undefined API");
		return 0;
	}

	IVertexArray* IVertexArray::Create() {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
				return new OpenGL::VertexArray();
			case IRendererAPI::API::NONE: break;
			default: break;
		}
		NE_CORE_ASSERT(false, "IVertexArray Create: Undefined API");
		return 0;
	}

	IShader* IShader::Create(const std::string& filepath, const ShaderType type) {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
				return new OpenGL::Shader(filepath, type);
			case IRendererAPI::API::NONE: break;
			default: break;
		}
		NE_CORE_ASSERT(false, "IProgram Create: Undefined API");
		return 0;
	}

	IProgram* IProgram::Create(const std::string& name, const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
				return new OpenGL::Program(name, vertexShaderFilePath, fragmentShaderFilePath);
			case IRendererAPI::API::NONE: break;
			default: break;
		}
		NE_CORE_ASSERT(false, "IProgram Create: Undefined API");
		return 0;
	}

	ITexture* ITexture::Create(const std::string& filepath, TextureType type) {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
				return new OpenGL::Texture(filepath, type);
			case IRendererAPI::API::NONE: break;
			default: break;
		}
		NE_CORE_ASSERT(false, "ITexture Create: Undefined API");
		return 0;
	}

	Renderer& Renderer::GetInstance() {
		static Renderer instance;
		if (!s_initialized && !Instantiate()) {
			NE_CORE_ASSERT(false, "Renderer: Failed to initialize");
		}
		return instance;
	}

	void Renderer::Init() {
		NE_CORE_ASSERT(Instantiate(), "Renderer: Failed to initialize");
	}

	bool Renderer::Instantiate() {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
				OpenGL::OpenGLContext::GetInstance().CreateContext();
				s_initialized = true;
				return true;
			case IRendererAPI::API::NONE: break;
			default: break;
		}
		return false;
	}

	void Renderer::Clear() const {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
				OpenGL::OpenGLContext::GetInstance().Clear();
			case IRendererAPI::API::NONE: break;
			default: break;
		}
	}

	void Renderer::Submit(std::shared_ptr<IVertexArray>& va, std::shared_ptr<IProgram>& program, const RenderMatrices& mats) {
		program->Bind();
		va->Bind();
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
				std::dynamic_pointer_cast<OpenGL::Program>(program)->SetUniform4f("vcolor", glm::vec4(1.0f));
				std::dynamic_pointer_cast<OpenGL::Program>(program)->SetUniformMat4("model", mats.transform);
				std::dynamic_pointer_cast<OpenGL::Program>(program)->SetUniformMat4("matrices.view_projection", mats.viewProjection);
				OpenGL::OpenGLContext::GetInstance().DrawIndexed(va);
			case IRendererAPI::API::NONE: break;
			default: break;
		}
		va->Unbind();
		program->Unbind();
	}
} // Neon
