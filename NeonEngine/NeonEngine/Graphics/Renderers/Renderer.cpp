#include "Graphics/Renderers/Renderer.h"

#include "nepch.h"

namespace Neon {
	bool Renderer::s_initialized = false;

	Renderer& Renderer::GetInstance() {
		static Renderer instance;
		if (!s_initialized && !Instantiate()) {
			NE_CORE_ASSERT(false, "Renderer: Failed to initialize");
		}
		return instance;
	}

	bool Renderer::Init() {
		if (Instantiate()) {
			return true;
		}

		NE_CORE_ASSERT(false, "Renderer: Failed to initialize");

		return false;
	}

	bool Renderer::Instantiate() {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL:
				OpenGL::OpenGLContext::GetInstance().CreateContext();
				s_initialized = true;
				return true;
			case IRendererAPI::API::NONE:
				break;
			default:
				break;
		}

		return false;
	}

	IRendererAPI& Renderer::GetRendererAPIInstance() const {
		switch(IRendererAPI::GetAPI()) {
			case IRendererAPI::API::OPENGL: return OpenGL::OpenGLContext::GetInstance();
			case IRendererAPI::API::NONE: break;
			default: break;
		}
		NE_CORE_ASSERT(false, "Renderer: Unable to return API instance");
	}

	void Renderer::Clear() const {
		GetRendererAPIInstance().Clear();
	}

	void Renderer::Submit(IVertexArray* va, IProgram* program, RenderMatrices mats) {
		program->Bind();
		va->Bind();
		//program->SetFloat4("vcolor", glm::vec4(1.0f));
		//program->SetMat4("model", mats.transform);
		//program->SetMat4("matrices.view_projection", mats.viewProjection);
		GetRendererAPIInstance().DrawIndexed(va);
		va->Unbind();
		program->Unbind();
	}

	void Renderer::Flush() {
		
	}
}
