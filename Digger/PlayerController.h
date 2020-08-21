#pragma once
#include <BaseComponent.h>
#include "BoxCollider2D.h"
#include "SpriteComponent.h"
#include "State.h"

enum class PlayerNumber : int
{
	P1 = 0,
	P2 = 1
};

enum class PlayerDirection : int
{
	Left = 0,
	Right = 1
};

class PlayerController : public dae::BaseComponent
{
public:
	PlayerController(PlayerNumber player = PlayerNumber::P1);
	PlayerController(const PlayerController& other) = delete;
	PlayerController(PlayerController&& other) noexcept = delete;
	PlayerController& operator=(const PlayerController& other) = delete;
	PlayerController& operator=(PlayerController&& other) noexcept = delete;
	~PlayerController() override;

	int GetControllerId() const { return m_ControllerId; }
	float GetWalkSpeed() const { return m_WalkSpeed; }

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
private:
	BoxCollider2D* m_pBoxCollider = nullptr;
	SpriteComponent* m_pSprite = nullptr;
	int m_ControllerId{};
	PlayerNumber m_PlayerNumber = PlayerNumber::P1;
	State* m_pActivState = nullptr;
	PlayerDirection m_PlayerDirection = PlayerDirection::Right;
	const float m_WalkSpeed = 10.0f;
};
