#include "Graphics/Cameras/Camera.h"

namespace Neon {
	Camera::Camera(const glm::vec3& pos, float fov, float aspect, float near, float far) {
		m_perspective = glm::perspective(glm::radians(fov), aspect, near, far);
		m_pos = pos;
		m_forward = m_dir = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_lookat = glm::lookAt(m_pos, m_pos + m_dir, m_up);
		m_yaw = m_pitch = 0.0;
	}

	void Camera::SetPosition(const glm::vec3 &n_pos) { 
		m_pos = n_pos;
	}

	void Camera::SetLookAt(const glm::vec3& n_pos) {
		m_lookat = glm::lookAt(m_pos, n_pos, m_up);
	}

	void Camera::RotateYaw(float angle) // Incremental rotate
	{
		m_yaw += angle;
	}

	void Camera::RotatePitch(float angle) {
		const float limit = 89.0 * glm::pi<float>() / 180.0;

		m_pitch += angle;

		if(m_pitch < -limit)
			m_pitch = -limit;

		if(m_pitch > limit)
			m_pitch = limit;
	}

	void Camera::Rotate(float angle) { // General rotate
		static const glm::vec4 UP(0.0f, 1.0f, 0.0f, 0.0f);

		glm::mat4 rotation = glm::rotate(angle, m_dir);

		m_forward = glm::normalize(rotation * glm::vec4(m_forward, 0.0f));
		m_up = glm::normalize(rotation * UP);
	}

	void Camera::Update() {
		m_dir.x = glm::sin(m_yaw) * glm::cos(m_pitch);
		m_dir.y = glm::sin(m_pitch);
		m_dir.z = glm::cos(m_yaw) * glm::cos(m_pitch);

		m_lookat = glm::lookAt(m_pos, m_pos + m_dir, m_up);
	}
}