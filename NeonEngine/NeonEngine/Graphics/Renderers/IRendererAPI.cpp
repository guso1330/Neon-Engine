#include "Graphics/Renderers/IRendererAPI.h"

#include "Core/Core.h"
// Interfaces
#include "Graphics/Renderers/IRendererAPI.h"
#include "Graphics/Renderers/IVertexArray.h"
#include "Graphics/Renderers/IProgram.h"
#include "Graphics/Renderers/ITexture.h"
#include "Graphics/Renderers/BufferLayout.h"
#include "Core/Platforms/OpenGL/OpenGLContext.h"

#include "nepch.h"

namespace Neon {
	#ifdef NE_PLATFORM_MACOS
		IRendererAPI::API IRendererAPI::s_API = IRendererAPI::API::OPENGL;
	#endif

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
} // Neon
