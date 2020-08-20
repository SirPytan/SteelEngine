#pragma once
#include "State.h"
#include "PlayerController.h"
#include "SpriteComponent.h"

class StandingState : public State
{
public:
	StandingState(dae::GameObject* pGameObject);
	~StandingState() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
};

class WalkLeftState : public State
{
public:
	WalkLeftState(dae::GameObject* pGameObject);
	~WalkLeftState() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};

class WalkRightState : public State
{
public:
	WalkRightState(dae::GameObject* pGameObject);
	~WalkRightState() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};

class JumpState : public State
{
public:
	JumpState(dae::GameObject* pGameObject);
	~JumpState() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};

class ShootBubble : public State
{
public:
	ShootBubble(dae::GameObject* pGameObject);
	~ShootBubble() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};

