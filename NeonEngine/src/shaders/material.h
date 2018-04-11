#pragma once

#include "texture.h"
#include "program.h"

#include <glm/glm.hpp>

namespace neon {
	struct Material {
		Material() {};
		Material(glm::vec3 &n_ambient, Texture *n_diffuse, Texture *n_specular, float shininess);

		// Variables
		glm::vec3 ambient = glm::vec3(1.0, 1.0, 1.0);
		Texture *diffuse = nullptr;
		Texture *specular = nullptr;
		float shininess = 1.0f;

		// Methods
		void Bind(Program *program) const {
			if(diffuse != nullptr) {
				diffuse->Bind(0);
				program->SetUniform1i("material.diffuse", 0);
			}
			if(specular != nullptr) {
				specular->Bind(1);
				program->SetUniform1i("material.specular", 1);
			}
		}

		void Unbind() const {
			if(diffuse != nullptr) {
				diffuse->Unbind(0);
			}
			if(specular != nullptr) {
				specular->Unbind(1);
			}
		}
	};
}