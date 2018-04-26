#include "./camera.h"

namespace neon {
	Camera::Camera(const glm::vec3& pos, float fov, float aspect, float near, float far) {
		m_perspective = glm::perspective(glm::radians(fov), aspect, near, far);
		m_pos = pos;
		m_forward = m_dir = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0, 1, 0);
		m_lookat = glm::lookAt(m_pos, m_pos + m_dir, m_up);
	}

	void Camera::SetPos(glm::vec3 &n_pos) { 
		m_pos = n_pos;
		m_lookat = glm::lookAt(m_pos, m_lookatPos, m_up);
	}

	void Camera::Update() {

	}
}