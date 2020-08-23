#include "PlayerController.h"
#include "InputManager.h"
#include <iostream>
#include "Commands.h"
#include "States.h"

using namespace SteelEngine;

PlayerController::PlayerController(PlayerNumber player)
: m_PlayerNumber{player}
{}

PlayerController::~PlayerController()
{
	delete m_pActivState;
	m_pActivState = nullptr;
}

void PlayerController::Initialize()
{
	m_pBoxCollider = m_pGameObject->GetComponent<BoxCollider2D>();
	m_pSprite = m_pGameObject->GetComponent<SpriteComponent>();

	if (m_PlayerNumber == PlayerNumber::P1)
	{
		for (int i{}; i < 4; i++)
		{
			if (InputManager::GetInstance().IsControllerConnected(i))
			{
				m_ControllerId = i;
				break;
			}
		}
	}
	else
	{
		//Gets second connected Player
		int counter{};
		for (int i{}; i < 4; i++)
		{
			if (InputManager::GetInstance().IsControllerConnected(i))
			{
				if (counter != 0)
				{
					m_ControllerId = i;
					break;
				}
				counter++;
			}
		}
		if (counter == 0)
		{
			std::cout << "There is no second controller connected\n";
		}
	}

	//For the First Player
	InputManager::GetInstance().AddCommand(new MoveLeft(m_ControllerId, GetGameObject()), SteelEngine::ControllerButton::DpadLeft);
	InputManager::GetInstance().AddCommand(new MoveRight(m_ControllerId, GetGameObject()), SteelEngine::ControllerButton::DpadRight);
	InputManager::GetInstance().AddCommand(new MoveUp(m_ControllerId, GetGameObject()), SteelEngine::ControllerButton::DpadUp);
	InputManager::GetInstance().AddCommand(new MoveDown(m_ControllerId, GetGameObject()), SteelEngine::ControllerButton::DpadDown);
	InputManager::GetInstance().AddCommand(new ShootFireball(m_ControllerId, GetGameObject()), SteelEngine::ControllerButton::A);

	m_pActivState = new StandingState(GetGameObject());
}

void PlayerController::Update(float deltaTime)
{
	if (m_pActivState != nullptr)
	{
		State* newState = m_pActivState->Update(deltaTime);
		if (newState != nullptr)
		{
			m_pActivState->Exit();
			delete m_pActivState;
			m_pActivState = newState;
			m_pActivState->Enter();
		}
	}
}

void PlayerController::Render()
{
}
