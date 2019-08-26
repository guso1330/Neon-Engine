#pragma once

#include "../core/platform/opengl/program.h"
#include "../core/platform/opengl/texture.h"

#include <glm/glm.hpp>

namespace Neon {

	class Material {
		public:
			Material() {};
			Material(glm::vec3 &n_ambient,
					 Texture *n_diffuse = nullptr,
					 Texture *n_specular = nullptr,
					 Texture *n_normal = nullptr,
					 Texture *n_height = nullptr,
					 Texture *n_occlusion = nullptr,
					 float shininess = 0.0f);

			inline const glm::vec3 &GetAmbient() const { return m_ambient; }
			inline const Texture* GetDiffuse() const { return m_diffuse; }
			inline const Texture* GetSpecular() const { return m_specular; }
			inline const Texture* GetNormal() const { return m_normal; }
			inline const Texture* GetHeight() const { return m_height; }
			inline const Texture* GetOcclusion() const { return m_occlusion; }
			inline const float &GetShininess() const { return m_shininess; }


			inline void SetDiffuse(Texture *n_diffuse) { m_diffuse = n_diffuse; }
			inline void SetSpecular(Texture *n_specular) { m_specular = n_specular; }
			inline void SetNormal(Texture *n_normal) { m_normal = n_normal; }
			inline void SetHeight(Texture *n_height) { m_height = n_height; }
			inline void SetOcclusion(Texture *n_occlusion) { m_occlusion = n_occlusion; }
			inline void SetAmbient(glm::vec3 &n_ambient) { m_ambient = n_ambient; }
			inline void SetShininess(float n_shininess) { m_shininess = n_shininess; }

			//
			// Methods
			//
			void Bind(Program *program) const;
			void Unbind() const;

		private:
			//
			// Variables
			//
			glm::vec3 m_ambient = glm::vec3(1.0, 1.0, 1.0);
			Texture *m_diffuse = nullptr;
			Texture *m_normal = nullptr;
			Texture *m_specular = nullptr;
			Texture *m_height = nullptr;
			Texture *m_occlusion = nullptr;
			float m_shininess = 0.0f;

	};
}