#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

void dae::GameObject::Destroy() {
	m_IsMarkedForDestroy = true;
}

bool dae::GameObject::IsMarkedForDestroy() {
	return m_IsMarkedForDestroy;
}

void dae::GameObject::Update(float elapsedSec){
	// Update
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) { component->Update(elapsedSec); });

	// Remove components marked for destroy
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) {
		if (component->IsMarkedForDestroy()) {
			m_pComponents.erase(std::remove(m_pComponents.begin(), m_pComponents.end(), component), m_pComponents.end());
		}
		});
}

void dae::GameObject::FixedUpdate(float elapsedSec) {
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [=](auto& component) { 
		component->FixedUpdate(elapsedSec); 
		});
}

void dae::GameObject::Render() const
{
	std::for_each(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) { component->Render();	});
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

glm::vec3 dae::GameObject::GetPosition() {
	return m_transform.GetPosition();
}
