#include "Commands.h"
#include "PlayerController.h"

class PlayerController;

MoveLeft::MoveLeft(int controllerId, GameObject* pPlayer)
	: Command(controllerId)
{
	PlayerController* pPlayerController = pPlayer->GetComponent<PlayerController>();
	if (pPlayerController)
		m_Input = pPlayerController->GetInput();
	else
		std::cout << "MoveLeft Command: GameObject has no PlayerController component.\n";
}

void MoveLeft::Execute()
{
	m_Input->direction = Direction::Left;
}

MoveRight::MoveRight(int controllerId, GameObject* pPlayer)
	: Command(controllerId)
{
	PlayerController* pPlayerController = pPlayer->GetComponent<PlayerController>();
	if (pPlayerController)
		m_Input = pPlayerController->GetInput();
	else
		std::cout << "MoveRight Command: GameObject has no PlayerController component.\n";
}

void MoveRight::Execute()
{
	m_Input->direction = Direction::Right;
}

MoveUp::MoveUp(int controllerId, GameObject* pPlayer)
	: Command(controllerId)
{
	PlayerController* pPlayerController = pPlayer->GetComponent<PlayerController>();
	if (pPlayerController)
		m_Input = pPlayerController->GetInput();
	else
		std::cout << "MoveUp Command: GameObject has no PlayerController component.\n";
}

void MoveUp::Execute()
{
	m_Input->direction = Direction::Up;
}

MoveDown::MoveDown(int controllerId, GameObject* pPlayer)
	: Command(controllerId)
{
	PlayerController* pPlayerController = pPlayer->GetComponent<PlayerController>();
	if (pPlayerController)
		m_Input = pPlayerController->GetInput();
	else
		std::cout << "MoveDown Command: GameObject has no PlayerController component.\n";
}

void MoveDown::Execute()
{
	m_Input->direction = Direction::Down;
}

ShootFireball::ShootFireball(int controllerId, GameObject* pPlayer)
	: Command(controllerId)
{
	PlayerController* pPlayerController = pPlayer->GetComponent<PlayerController>();
	if (pPlayerController)
		m_Input = pPlayerController->GetInput();
	else
		std::cout << "ShootFireball Command: GameObject has no PlayerController component.\n";
}

void ShootFireball::Execute()
{
	m_Input->shootFireball = true;
}
