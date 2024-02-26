#pragma once
#include "Component.h"
#include <string>

class TextRenderComponent;

class FPSComponent : public Component
{
public:
	FPSComponent(dae::GameObject* pOwner);
	virtual ~FPSComponent() = default;

	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) = delete;

	virtual void Update(float elapsedSec);
	virtual void FixedUpdate(float) {}

protected:
	float m_Fps;
	float m_PreviousFps{};
	TextRenderComponent* m_pTextRenderer;
};
