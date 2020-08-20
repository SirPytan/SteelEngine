#include "PlayerController.h"
#include "InputManager.h"
#include <iostream>

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
