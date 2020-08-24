#include "SteelEnginePCH.h"
#include "ScoreScriptComponent.h"
#include <sstream>

ScoreScriptComponent::ScoreScriptComponent(ScoreObserver* pScoreObserver)
	: m_pScoreObserver{pScoreObserver}
{
}

ScoreScriptComponent::~ScoreScriptComponent()
{
	m_pScoreObserver = nullptr;
	m_pTextRenderComponent = nullptr;
}

void ScoreScriptComponent::Initialize()
{
	m_pTextRenderComponent = GetGameObject()->GetComponent<TextRenderComponent>();
}

void ScoreScriptComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_pScoreObserver != nullptr && m_pTextRenderComponent != nullptr)
	{
		int score = m_pScoreObserver->GetScore();
		if (m_Score != score)
		{
			std::stringstream ss{};
			ss << "Score: " << score;
			m_pTextRenderComponent->SetText(ss.str());
			m_Score = score;
		}
	}
}

void ScoreScriptComponent::Render()
{
}
