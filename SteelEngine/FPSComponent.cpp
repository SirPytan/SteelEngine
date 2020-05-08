#include "SteelEnginePCH.h"
#include "FPSComponent.h"

FPSComponent::FPSComponent()
{}

void FPSComponent::Initialize()
{}

void FPSComponent::Update(float deltaTime)
{
	if (m_Active)
	{
		m_FPSTimer += deltaTime;
		++m_FPSCounter;
		if (m_FPSTimer >= 1.0f)
		{
			m_FPS = m_FPSCounter;
			m_FPSCounter = 0;
			//m_FPSTimer -= 1.0f;
			m_FPSTimer = 0.0f;
		}
	}
}

void FPSComponent::Render()
{}
