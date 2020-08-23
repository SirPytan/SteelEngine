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

class GoLeftState : public State
{
public:
	GoLeftState(dae::GameObject* pGameObject);
	~GoLeftState() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};

class GoRightState : public State
{
public:
	GoRightState(dae::GameObject* pGameObject);
	~GoRightState() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};

class GoDownState : public State
{
public:
	GoDownState(dae::GameObject* pGameObject);
	~GoDownState() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};

class GoUpState : public State
{
public:
	GoUpState(dae::GameObject* pGameObject);
	~GoUpState() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};


class ShootFireball : public State
{
public:
	ShootFireball(dae::GameObject* pGameObject);
	~ShootFireball() = default;
	void Enter() override;
	State* Update(float deltaTime) override;
	void Exit() override;
private:
	PlayerController* m_pPlayerController = nullptr;
	SpriteComponent* m_pSprite = nullptr;
};

