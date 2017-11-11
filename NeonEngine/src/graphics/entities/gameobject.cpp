#include "./gameobject.h"

namespace neon {
	GameObject::GameObject() { 
		m_model = nullptr;
		m_position = glm::vec3(0.0);
		m_scale = glm::vec3(1.0f);
		m_rotation = glm::vec3(0.0);
	}
	GameObject::GameObject(Model *n_model) {
		m_model = n_model;
		m_position = glm::vec3(0.0);
		m_scale = glm::vec3(1.0f);
		m_rotation = glm::vec3(0.0);
	}

	GameObject::~GameObject() { /* TODO: should delete model? */ }

	void GameObject::SetPosition(const glm::vec3 &n_pos) { 
		m_position = n_pos;
		SetModelMatrix();
	}

	void GameObject::SetScale(const glm::vec3 &n_scale) { 
		m_scale = n_scale;
		SetModelMatrix();
	}

	void GameObject::SetRotation(const float n_angle, const glm::vec3 &n_rotation) {
		m_rotation = n_rotation;
		m_angle = n_angle;
		SetModelMatrix();
	}

	void GameObject::SetModelMatrix() {
		m_model->SetModelMatrix(glm::translate(m_position) * glm::rotate(m_angle, m_rotation) * glm::scale(m_scale));
	}

	void GameObject::Draw() {
		m_model->Draw();
	}
}