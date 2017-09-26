#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace neon {
	class Camera {
		public: 
			Camera(const glm::vec3& pos, float fov, float aspect, float near, float far);

			inline glm::mat4 GetViewProjection() const { return m_perspective * glm::lookAt(m_pos, m_pos + m_forward, m_up); }
		
		private:	
			glm::mat4 m_perspective;
			glm::vec3 m_pos;
			glm::vec3 m_forward;
			glm::vec3 m_up;
	};
}