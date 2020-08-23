#pragma once
#include "SteelEnginePCH.h"
#include "States.h"
//#include <winnt.h>
#include "InputManager.h"

using namespace SteelEngine;

StandingState::StandingState(dae::GameObject* pGameObject)
    : State(pGameObject)
{
    m_pPlayerController = pGameObject->GetComponent<PlayerController>();
}

void StandingState::Enter()
{
}

State* StandingState::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);

    //Use Commands
    if (m_pPlayerController != nullptr)
    {
        if (m_pPlayerController->GetInput()->direction == Direction::Left)
        {
            return new GoLeftState(m_pGameObject);
        }

        if (m_pPlayerController->GetInput()->direction == Direction::Right)
        {
            return new GoRightState(m_pGameObject);
        }

        if (m_pPlayerController->GetInput()->direction == Direction::Up)
        {
            return new GoUpState(m_pGameObject);
        }

        if (m_pPlayerController->GetInput()->direction == Direction::Down)
        {
            return new GoDownState(m_pGameObject);
        }

        if (m_pPlayerController->GetInput()->shootFireball)
        {
            return new ShootFireballState(m_pGameObject);
        }
    }

    return nullptr;
}

void StandingState::Exit()
{
}
//-------------------------------------------------------------------


GoLeftState::GoLeftState(dae::GameObject* pGameObject)
    : State(pGameObject)
{
    m_pPlayerController = pGameObject->GetComponent<PlayerController>();
    m_pSprite = pGameObject->GetComponent<SpriteComponent>();
}

void GoLeftState::Enter()
{
    m_pSprite->SetAnimationParameters(AnimationType::FromLeftToRight, 1, 2, false);
}

State* GoLeftState::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);
    if (m_pPlayerController->GetInput()->direction == Direction::Left)
    {
        //auto pos = m_pGameObject->GetPosition2D();
        //pos.x -= deltaTime * m_pPlayerController->GetWalkSpeed();
        //m_pGameObject->SetPosition(pos.x, pos.y);
        return nullptr;
    }

    return new StandingState(m_pGameObject);
}

void GoLeftState::Exit()
{
}

//-------------------------------------------------------------------

GoRightState::GoRightState(dae::GameObject* pGameObject)
    : State(pGameObject)
{
    m_pPlayerController = pGameObject->GetComponent<PlayerController>();
    m_pSprite = pGameObject->GetComponent<SpriteComponent>();
}

void GoRightState::Enter()
{
    m_pSprite->SetAnimationParameters(AnimationType::FromLeftToRight, 1, 1, false);
}

State* GoRightState::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);
    if (m_pPlayerController->GetInput()->direction == Direction::Right)
    {
        //auto pos = m_pGameObject->GetPosition2D();
        //pos.x += deltaTime * m_pPlayerController->GetWalkSpeed();
        //m_pGameObject->SetPosition(pos.x, pos.y);
        return nullptr;
    }

    return new StandingState(m_pGameObject);
}

void GoRightState::Exit()
{
}


//-------------------------------------------------------------------

GoDownState::GoDownState(dae::GameObject* pGameObject)
    : State(pGameObject)
{
}

void GoDownState::Enter()
{
}

State* GoDownState::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);
    if (m_pPlayerController->GetInput()->direction == Direction::Down)
    {
        //auto pos = m_pGameObject->GetPosition2D();
        //pos.x += deltaTime * m_pPlayerController->GetWalkSpeed();
        //m_pGameObject->SetPosition(pos.x, pos.y);
        return nullptr;
    }

    return new StandingState(m_pGameObject);
}

void GoDownState::Exit()
{
}

//-------------------------------------------------------------------

GoUpState::GoUpState(dae::GameObject* pGameObject)
    : State(pGameObject)
{
}

void GoUpState::Enter()
{
}

State* GoUpState::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);
    if (m_pPlayerController->GetInput()->direction == Direction::Up)
    {
        //auto pos = m_pGameObject->GetPosition2D();
        //pos.x += deltaTime * m_pPlayerController->GetWalkSpeed();
        //m_pGameObject->SetPosition(pos.x, pos.y);
        return nullptr;
    }

    return new StandingState(m_pGameObject);
}

void GoUpState::Exit()
{
}

//-------------------------------------------------------------------

ShootFireballState::ShootFireballState(dae::GameObject* pGameObject)
    : State(pGameObject)
{
    m_pPlayerController = pGameObject->GetComponent<PlayerController>();
    m_pSprite = pGameObject->GetComponent<SpriteComponent>();
}

void ShootFireballState::Enter()
{
}

State* ShootFireballState::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);
    return nullptr;
}

void ShootFireballState::Exit()
{
}
