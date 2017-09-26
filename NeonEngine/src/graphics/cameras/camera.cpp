#include "./camera.h"

namespace neon {
	Camera::Camera(const glm::vec3& pos, float fov, float aspect, float near, float far) {
		m_perspective = glm::perspective(fov, aspect, near, far);
		m_pos = pos;
		m_forward = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);
	}
}