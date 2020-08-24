#pragma once
#include <BaseComponent.h>
#include "ScoreObserver.h"
#include "TextRenderComponent.h"

class ScoreScriptComponent : public dae::BaseComponent
{
public:
	ScoreScriptComponent(ScoreObserver* pScoreObserver);
	~ScoreScriptComponent();

	ScoreScriptComponent(const ScoreScriptComponent& other) = delete;
	ScoreScriptComponent(ScoreScriptComponent&& other) noexcept = delete;
	ScoreScriptComponent& operator=(const ScoreScriptComponent& other) = delete;
	ScoreScriptComponent& operator=(ScoreScriptComponent&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
private:
	ScoreObserver* m_pScoreObserver = nullptr;
	TextRenderComponent* m_pTextRenderComponent = nullptr;
	int m_Score{};
};

