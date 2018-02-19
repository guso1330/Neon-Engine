#include "./transform.h"

namespace neon {
	Transform::Transform() :
		m_position(glm::vec3(0.0)),
		m_scale(glm::vec3(1.0f)),
		m_rotation(glm::vec3(1.0f)),
		m_modelMatrix(glm::mat4(1.0f)) {
			m_angle = 0.0f;
		}

	Transform::Transform(glm::vec3 &n_pos, glm::vec3 &n_scale, glm::vec3 &n_rotation) {
		m_position = n_pos;
		m_scale = n_scale;
		m_rotation = n_rotation;
		m_angle = 0.0f;
		m_modelMatrix = glm::mat4(1.0f);
	}

	Transform::~Transform() {}

	void Transform::SetPosition(const glm::vec3 &n_pos) { 
		m_position = n_pos;
		SetModelMatrix();
	}

	void Transform::SetScale(const glm::vec3 &n_scale) { 
		m_scale = n_scale;
		SetModelMatrix();
	}

	void Transform::SetRotation(const float n_angle, const glm::vec3 &n_rotation) {
		m_rotation = n_rotation;
		m_angle = n_angle;
		SetModelMatrix();
	}

	void Transform::SetModelMatrix() {
		m_modelMatrix = glm::translate(m_position) * glm::rotate(m_angle, m_rotation) * glm::scale(m_scale);
	}

}