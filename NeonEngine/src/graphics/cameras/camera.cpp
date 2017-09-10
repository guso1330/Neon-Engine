//
// Camera Class
//
// TODO: you should rewrite this and really make sure it is working.
//		 Think about replacing data types from vec3 to vec4. Google
//		 the pros and cons of using one versus the other, and when
//		 it's appropriate to use one over the other.

#include "camera.h"
#include <iostream>

namespace neon {

	// WARNING: JUST A QUICK FIX
	glm::mat4 RotateY( const GLfloat theta ) {
		GLfloat angle = (M_PI / 180.0) * theta;

		glm::mat4 c;
		c[2][2] = c[0][0] = glm::cos(angle);
		c[0][2] = glm::sin(angle);
		c[2][0] = -c[0][2];
		return c;
	}

	Camera::Camera(const glm::vec4 &pos, float fov, float aspect, float near, float far) {
		this->pos = pos;
		this->forward = this->dir = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
		this->up = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, near, far);
		yaw = pitch = 0.0;
	}

	glm::mat4 Camera::GetViewProjection() const { 
		return projection * glm::lookAt(glm::vec3(pos), glm::vec3(pos+dir), glm::vec3(up));
	}

	void Camera::MoveForward(float amt) {
		float lx = glm::sin(yaw)*glm::cos(pitch);
		float ly = glm::sin(pitch);
		float lz = glm::cos(yaw)*glm::cos(pitch);

		// std::cout << lx << " " << " " << ly << " " << lz << std::endl;

		pos.x = pos.x + amt*lx;
		pos.y = pos.y + amt*ly;
		pos.z = pos.z + amt*lz;

		Update();
	}

	void Camera::MoveRight(float amt) {
		pos += glm::vec4(glm::cross(glm::vec3(up), glm::vec3(dir)) * amt, 1.0);
		Update();
	}

	void Camera::RotateYaw(float angle) // Incremental rotate
	{
		yaw += angle;

		Update();
	}

	void Camera::RotatePitch(float angle) {
		const float limit = 89.0 * M_PI / 180.0;

		pitch += angle;

		if(pitch < -limit)
			pitch = -limit;

		if(pitch > limit)
			pitch = limit;

		Update();
	}

	void Camera::Rotate(float angle) { // General rotate
		static const glm::vec4 UP(0.0f, 1.0f, 0.0f, 0.0f);

		glm::mat4 rotation = RotateY(angle);

		forward = glm::vec4(glm::normalize(rotation * forward));
		up = glm::vec4(glm::normalize(rotation * up));

		Update();
	}

	void Camera::Update() {
		dir.x = glm::sin(yaw) * glm::cos(pitch);
		dir.y = glm::sin(pitch);
		dir.z = glm::cos(yaw) * glm::cos(pitch);

		strafe_x = glm::cos(yaw - M_PI_2);
		strafe_z = glm::sin(yaw - M_PI_2);
	}
}