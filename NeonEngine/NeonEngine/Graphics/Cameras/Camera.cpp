#include "Graphics/Cameras/Camera.h"

namespace Neon {
	bool Camera::Init(OrthagraphicCameraSettings& settings) {
		float left;
		float right;
		float bottom;
		float top;
		float nearPlane;
		float farPlane;

		left = settings.left;
		right = settings.right;
		bottom = settings.bottom;
		top = settings.top;
		nearPlane = settings.nearPlane;
		farPlane = settings.farPlane;

		m_projection = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
		m_pos = settings.position;

		Initialize();

		return true;
	}

	bool Camera::Init(PerspectiveCameraSettings& settings) {
		float fov;
		float aspect;
		float nearPlane;
		float farPlane;

		fov = settings.fov;
		aspect = settings.aspect;
		nearPlane = settings.nearPlane;
		farPlane = settings.farPlane;

		m_projection = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
		m_pos = settings.position;

		Initialize();

		return true;
	}

	void Camera::Initialize() {
		m_forward = glm::vec3(0, 0, 1);
		m_dir = glm::vec3(0, 0, 1);
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_lookat = glm::lookAt(m_pos, m_pos + m_dir, m_up);
		m_yaw = 0.0f;
		m_pitch = 0.0f;
	}

	/* Getters */
	// TODO: Modify the way that this ViewProjection Matrix is calculated
	const glm::mat4& Camera::GetViewProjection() const {
		glm::mat4 result;
		result = m_projection * m_lookat;
		return result;
	}

	/* Setters */
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