#include "./ambientLight.h"

namespace neon {
	AmbientLight::AmbientLight() {
		m_shaders.push_back(new Shader("./NeonEngine/src/res/shaders/lightShaders/ambientLightVShader.glsl", GL_VERTEX_SHADER));
		m_shaders.push_back(new Shader("./NeonEngine/src/res/shaders/lightShaders/ambientLightFShader.glsl", GL_FRAGMENT_SHADER));

		m_program = new Program(m_shaders);

		m_intensity = 0.2f;
		m_diffuse = glm::vec3(1.0f);
	}

	AmbientLight::~AmbientLight() {
		for(std::vector<Shader*>::iterator it=m_shaders.begin(); it != m_shaders.end(); ++it) {
			delete (*it);
		}
		delete m_program;
	}

	void AmbientLight::Bind(Renderable3d* renderable, Camera* camera) {
		m_program->Bind();
		renderable->GetVao()->Bind();
		renderable->GetIbo()->Bind();

		m_program->SetUniformMat4("view_projection", camera->GetViewProjection());
		m_program->SetUniformMat4("model", renderable->GetTransform().GetModelMatrix());
		m_program->SetUniform4f("vcolor", renderable->GetColor());

		m_program->SetUniform1f("light.intensity", m_intensity);
		m_program->SetUniform3f("light.diffuse",m_diffuse);

		// Set Up material
		const Material* mat = renderable->GetMaterial();
		const Texture* diffuse = mat->GetDiffuse();

		if(diffuse != nullptr) {
			mat->GetDiffuse()->Bind(0);
			m_program->SetUniform1i("material.diffuse", 0);
			m_program->SetUniform3f("material.ambient", mat->GetAmbient());
		}
	}

	void AmbientLight::Unbind() {
		m_program->Unbind();
	}
}