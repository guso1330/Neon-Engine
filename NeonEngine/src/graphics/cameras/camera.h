#pragma once

#include <glad/glad.h>
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/detail/func_geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace neon {
	struct Camera {
		public:
			Camera(const glm::vec4 &pos, float fov, float aspect, float near, float far);

			glm::mat4 GetViewProjection() const;
			void MoveForward(float amt);
			void MoveRight(float amt);
			void RotateYaw(float angle);
			void RotatePitch(float angle);
			void Rotate(float angle);
			void Update();

			inline void SetProjection(glm::mat4 nprojection) { projection = nprojection; }
			inline void SetPos(glm::vec4 npos) { pos = npos; }
			inline void SetDir(glm::vec4 ndir) { dir = ndir; }
			inline void SetYaw(float angle) { yaw = angle; }
			inline void SetPitch(float angle) { pitch = angle; }
			inline void SetDirToForward() { dir = forward; }
			inline glm::vec4 GetPos() { return pos; }
			inline glm::vec4 GetDir() { return dir; }
			inline float GetYaw() { return yaw; }

		private:
			glm::mat4 projection;
			glm::vec4 pos;
			glm::vec4 forward;
			glm::vec4 up;

			glm::vec4 dir;
			float yaw, pitch;
			float strafe_x, strafe_z; // Always gonna be 90 degrees to the direction vector
	};
}