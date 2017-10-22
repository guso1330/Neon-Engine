#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace neon {
	class Camera {
		public: 
			Camera(const glm::vec3& pos, float fov, float aspect, float near, float far);
			inline glm::mat4 GetViewProjection() const { return m_perspective * m_lookat; }
			inline glm::mat4 GetViewMatrix() const { return m_lookat; }

			inline void SetLookAt(const glm::vec3& n_pos) { m_lookat = glm::lookAt(m_pos, n_pos, m_up); }
			
		private:	
			glm::mat4 m_perspective, m_lookat;
			glm::vec3 m_pos;
			glm::vec3 m_forward, m_dir;
			glm::vec3 m_up;
	};
}