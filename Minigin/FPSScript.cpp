#include "MiniginPCH.h"
#include "FPSScript.h"

FPSScript::FPSScript()
{}

void FPSScript::Initialize()
{
	m_pFPSComponent = m_pGameObject->GetComponent<FPSComponent>();
	m_pTextRenderComponent = m_pGameObject->GetComponent<TextRenderComponent>();
}

void FPSScript::Update(float deltaTime)
{
	if (m_pFPSComponent != nullptr && m_pTextRenderComponent != nullptr)
	{
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime >= m_FPSRefreshInterval)
		{
			m_ElapsedTime = 0;
			m_pTextRenderComponent->SetText(std::to_string(m_pFPSComponent->GetFPS()));
		}
	}
	else
	{
		std::cout << "m_pFPSComponent and or m_pTextRenderComponent are nullpointer\n";
	}

}

void FPSScript::Render()
{
}
