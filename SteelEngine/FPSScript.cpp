#include "SteelEnginePCH.h"
#include "FPSScript.h"
#include <sstream>

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
			std::stringstream ss;
			ss << "FPS: " << m_pFPSComponent->GetFPS();
			m_pTextRenderComponent->SetText(ss.str());
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
