#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

namespace neon {
	class Camera {
		public: 
			Camera(const glm::vec3& pos, float fov, float aspect, float near, float far);
			inline glm::mat4 GetViewProjection() const { return m_perspective * m_lookat; }
			inline glm::mat4 GetViewMatrix() const { return m_lookat; }
			inline const glm::vec3 &GetPos() const { return m_pos; }

			void SetPos(glm::vec3 &n_pos);
			void SetLookAt(const glm::vec3& n_pos);

			virtual void Update();
			
		private:	
			glm::mat4 m_perspective, m_lookat;
			glm::vec3 m_lookatPos;
			glm::vec3 m_pos;
			glm::vec3 m_forward, m_dir;
			glm::vec3 m_up;

		// DEBUG CAMERA STUFF
		// if(DEBUG_CAM) {
		// 	int dx = x - WIN_W/2;
		// 	int dy = y - WIN_H/2;
		// 	if(dx) { // get rotation in the x direction
		// 		camera.RotateYaw(-camera_rotate_speed*dx);
		// 	}
		// 	if(dy) {
		// 		camera.RotatePitch(-camera_rotate_speed*dy);
		// 	}

		// 	glutWarpPointer(WIN_W/2, WIN_H/2);

		// 	just_warped = true;
		// }
	};
}