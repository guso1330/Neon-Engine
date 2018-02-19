#pragma once

#include "./model.h"
#include "./transform.h"

namespace neon {
	class GameObject {
		public: 
			GameObject();
			GameObject(Model *model);
			~GameObject();

			const glm::mat4 &GetModelMatrix() const { return m_transform.GetModelMatrix(); }

			void SetPosition(const glm::vec3 &n_pos);
			void SetScale(const glm::vec3 &n_scale);
			void SetRotation(const float n_angle, const glm::vec3 &n_rotation);

			void Draw();

		private:
			Model *m_model;
			Transform m_transform;
	};
}