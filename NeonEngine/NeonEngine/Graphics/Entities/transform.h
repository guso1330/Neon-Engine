#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext.hpp>
#include <glm/glm.hpp>

namespace Neon {
	class Transform {
		public:
			Transform();
			Transform(glm::vec3 &n_pos, glm::vec3 &n_scale, glm::vec3 &n_rotation);
			~Transform();
		
		public:
			// Getters
			inline const glm::mat4 &GetModelMatrix() const { return m_modelMatrix; }
			inline const glm::vec3 &GetPosition() const { return m_position; }
			inline const glm::vec3 &GetRotation() const { return m_rotation; }
			inline const glm::vec3 &GetScale() const { return m_scale; }


			// Setters
			inline void SetModelMatrix(const glm::mat4 &n_modelMatrix) { m_modelMatrix = n_modelMatrix; }
			void SetPosition(const glm::vec3 &n_pos);
			void SetScale(const glm::vec3 &n_scale);
			void SetRotation(const float n_angle, const glm::vec3 &n_rotation);

		private:
			void SetModelMatrix();
			
		private:
			float m_angle;
			glm::vec3 m_position;
			glm::vec3 m_scale;
			glm::vec3 m_rotation;
			glm::mat4 m_modelMatrix;
	};
}
