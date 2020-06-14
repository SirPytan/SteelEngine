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

class PlayerController : public dae::BaseComponent
{
public:
	PlayerController(PlayerNumber player = PlayerNumber::P1);
	PlayerController(const PlayerController& other) = delete;
	PlayerController(PlayerController&& other) noexcept = delete;
	PlayerController& operator=(const PlayerController& other) = delete;
	PlayerController& operator=(PlayerController&& other) noexcept = delete;
	~PlayerController() override;

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
};
