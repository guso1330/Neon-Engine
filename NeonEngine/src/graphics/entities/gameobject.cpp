#include "./gameobject.h"

namespace neon {
	GameObject::GameObject() { 
		m_model = nullptr;
	}
	GameObject::GameObject(Model *n_model) {
		m_model = n_model;
	}

	GameObject::~GameObject() { /* TODO: should delete model? */ }

	void GameObject::SetPosition(const glm::vec3 &n_pos) { 
		if(m_model != nullptr) {
			m_transform.SetPosition(n_pos);
		}
	}

	void GameObject::SetScale(const glm::vec3 &n_scale) { 
		if(m_model != nullptr) {
			m_transform.SetScale(n_scale);
		}
	}

	void GameObject::SetRotation(const float n_angle, const glm::vec3 &n_rotation) {
		if(m_model != nullptr) {
			m_transform.SetRotation(n_angle, n_rotation);
		}
	}

	void GameObject::Draw() {
		if(m_model != nullptr) {
			m_model->Draw(m_transform.GetModelMatrix());
		}
	}
}