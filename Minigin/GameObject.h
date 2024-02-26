#pragma once
#include <memory>
#include "Transform.h"
#include <string>
#include "Component.h"
#include <vector>
#include <algorithm>

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject final
	{
	public:
		virtual void Update(float elapsedSec);
		void FixedUpdate(float elapsedSec);
		virtual void Render() const;

		void SetPosition(float x, float y);
		glm::vec3 GetPosition();

		GameObject() = default;
		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template<typename ComponentType, typename... Args>
		ComponentType* AddComponent(Args&&... arguments) {
			std::unique_ptr<ComponentType> component{ std::make_unique<ComponentType>(this, std::forward<Args>(arguments)...) };
			m_pComponents.push_back(std::move(component));
			return GetComponent<ComponentType>();
		}

		template<typename ComponentType>
		ComponentType* GetComponent() const {
			auto foundComponent = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) {
				return typeid(*(component.get())) == typeid(ComponentType);
				});

			if (foundComponent != m_pComponents.end()) {
				return static_cast<ComponentType*>((*foundComponent).get());
			}
			return nullptr;
		}

		template<typename ComponentType>
		std::vector<ComponentType*> GetComponents() const {

			std::vector<ComponentType*> pComponents{};

			std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](const auto& component) {
				if (typeid(*(component.get())) == typeid(ComponentType)) {
					pComponents.push_back(static_cast<ComponentType*>(component.get()));
				}
				});

			return pComponents;
		}

		template<typename ComponentType>
		bool RemoveComponent() const {
			auto foundComponent = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const auto& component) {
				return typeid(*(component.get())) == typeid(ComponentType);
				});

			if (foundComponent != m_pComponents.end()) {
				(*foundComponent)->Destroy();
				return true;
			}
			return false;
		}

		template<typename ComponentType>
		void RemoveComponents() const {

			std::for_each(m_pComponents.begin(), m_pComponents.end(), [&](auto& component) {
				if (typeid(*(component.get())) == typeid(ComponentType)) {
					component->Destroy();
				}
				});
		}

		bool IsMarkedForDestroy();
		void Destroy();

	private:
		Transform m_transform{};

		bool m_IsMarkedForDestroy{ false };

		std::vector<std::unique_ptr<Component>> m_pComponents;
	};
}
