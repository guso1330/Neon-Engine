#pragma once

#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"

namespace Neon {
	struct CameraSettings {
		float nearPlane;
		float farPlane;
		glm::vec3 position;
	};

	struct OrthagraphicCameraSettings : public CameraSettings {
		float left;
		float right;
		float bottom;
		float top;
	};

	struct PerspectiveCameraSettings : public CameraSettings {
		float aspect;
		float fov;
	};

	class Camera {
		public: 
			Camera() = default;

			/* Getters */
			inline const float GetPitch() const { return m_pitch; }
			inline const float GetYaw() const { return m_yaw; }
			inline const glm::vec3& GetPosition() const { return m_pos; }
			inline const glm::vec3& GetRelativeUp() const { return m_up; }
			inline const glm::vec3& GetDirection() const { return m_dir; }
			inline const glm::mat4& GetProjection() const { return m_projection; }
			inline const glm::mat4& GetViewMatrix() const { return m_lookat; }
			const glm::mat4& GetViewProjection();

			/* Setters */
			void SetLookAt(const glm::vec3& n_pos);
			void SetPitch(const float pitch) { m_pitch = pitch; }
			void SetPosition(const glm::vec3& n_pos);
			void SetYaw(const float yaw) { m_yaw = yaw; }

			/* Mutators */
			void RotateYaw(float angle);
			void RotatePitch(float angle);
			void Rotate(float angle);

			/* Member Functions */
			bool Init(OrthagraphicCameraSettings& settings);
			bool Init(PerspectiveCameraSettings& settings);
			void Update();

		private:
			void Initialize();
		private:
			float m_yaw;
			float m_pitch;
			glm::vec3 m_dir;
			glm::vec3 m_pos;
			glm::vec3 m_forward;
			glm::vec3 m_up;
			glm::mat4 m_viewProjection;
			glm::mat4 m_projection;
			glm::mat4 m_lookat;
	};
}
