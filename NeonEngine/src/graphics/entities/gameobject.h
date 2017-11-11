#pragma once

#include "./model.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace neon {
	class GameObject {
		public: 
			GameObject();
			GameObject(Model *model);
			~GameObject();

			void Draw();

			void SetPosition(const glm::vec3 &n_pos);
			void SetScale(const glm::vec3 &n_scale);
			void SetRotation(const float n_angle, const glm::vec3 &n_rotation);

		private: 
			void SetModelMatrix();

		private:
			Model *m_model;

			float m_angle;

			// TODO: make these glm::mat4's?
			glm::vec3 m_position;
			glm::vec3 m_scale;
			glm::vec3 m_rotation;
	};
}