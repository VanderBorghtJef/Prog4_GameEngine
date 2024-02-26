#include "FPSComponent.h"
#include "GameObject.h"
#include "TextRenderComponent.h"

FPSComponent::FPSComponent(dae::GameObject* pOwner)
	: Component(pOwner)
	, m_Fps{ 0.0f }
{
	m_pTextRenderer = m_pOwner->GetComponent<TextRenderComponent>();
}

void FPSComponent::Update(float elapsedSec) 
{
	m_Fps = 1.0f / elapsedSec;

	if (m_Fps != m_PreviousFps)
	{
		m_PreviousFps = m_Fps;
		if (m_pTextRenderer) {
			m_pTextRenderer->SetText(std::to_string(int(m_Fps)) + " FPS");
		}
	}

}

//m_delay += GTime().GetInstance().GetDeltaTime();
//m_count++;
//
//if (m_delay >= m_max_delay)
//{
//	m_text->SetText(std::format("[:.1]", m_count / m_delay))
//		//more code
//}