#include "material.h"

namespace neon {
	Material::Material(glm::vec3 &n_ambient,
					   Texture *n_diffuse,
					   Texture *n_specular,
					   Texture *n_normal,
					   Texture *n_height,
					   Texture *n_occlusion,
					   float n_shininess) {
		m_ambient = n_ambient;
		m_diffuse = n_diffuse;
		m_specular = n_specular;
		m_normal = n_normal;
		m_occlusion = n_occlusion;
		m_shininess = n_shininess;
	}

	void Material::Bind(Program *program) const {
		program->SetUniform3f("material.ambient", m_ambient);

		if(m_diffuse != nullptr) {
			m_diffuse->Bind(0);
			program->SetUniform1i("material.diffuse", 0);
		}
		if(m_specular != nullptr) {
			m_specular->Bind(1);
			program->SetUniform1i("material.specular", 1);
		}
		if(m_normal != nullptr) {
			m_normal->Bind(2);
			program->SetUniform1i("material.normal", 2);
		}
		if(m_height != nullptr) {
			m_height->Bind(3);
			program->SetUniform1i("material.height", 3);
		}
		if(m_occlusion != nullptr) {
			m_occlusion->Bind(4);
			program->SetUniform1i("material.occlusion", 4);
		}
	}

	void Material::Unbind() const {
		if(m_diffuse != nullptr) {
			m_diffuse->Unbind(0);
		}
		if(m_specular != nullptr) {
			m_specular->Unbind(1);
		}
		if(m_normal != nullptr) {
			m_normal->Unbind(2);
		}
		if(m_height != nullptr) {
			m_height->Unbind(3);
		}
		if(m_occlusion != nullptr) {
			m_occlusion->Unbind(4);
		}
	}
}