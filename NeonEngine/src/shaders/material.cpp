#include "material.h"

namespace neon {
	Material::Material(glm::vec3 &n_ambient, Texture *n_diffuse, Texture *n_specular, float n_shininess) {
		ambient = n_ambient;
		diffuse = n_diffuse;
		specular = n_specular;
		shininess = n_shininess;
	}
}