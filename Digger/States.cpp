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

    if (InputManager::GetInstance().IsPressed(ControllerButton::DpadLeft, m_pPlayerController->GetControllerId()))
    {
        return new GoLeftState(m_pGameObject);
    }
    if (InputManager::GetInstance().IsPressed(ControllerButton::DpadRight, m_pPlayerController->GetControllerId()))
    {
        return new GoRightState(m_pGameObject);
    }

    if (InputManager::GetInstance().IsPressed(ControllerButton::X, m_pPlayerController->GetControllerId()))
    {
        return new ShootFireball(m_pGameObject);
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
    if (InputManager::GetInstance().IsPressed(ControllerButton::DpadLeft, m_pPlayerController->GetControllerId()))
    {
        auto pos = m_pGameObject->GetPosition2D();
        pos.x -= deltaTime * m_pPlayerController->GetWalkSpeed();
        m_pGameObject->SetPosition(pos.x, pos.y);
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
    if (InputManager::GetInstance().IsPressed(ControllerButton::DpadRight, m_pPlayerController->GetControllerId()))
    {
        auto pos = m_pGameObject->GetPosition2D();
        pos.x += deltaTime * m_pPlayerController->GetWalkSpeed();
        m_pGameObject->SetPosition(pos.x, pos.y);
        return nullptr;
    }

    return new StandingState(m_pGameObject);
}

void GoRightState::Exit()
{
}

//-------------------------------------------------------------------

ShootFireball::ShootFireball(dae::GameObject* pGameObject)
    : State(pGameObject)
{
    m_pPlayerController = pGameObject->GetComponent<PlayerController>();
    m_pSprite = pGameObject->GetComponent<SpriteComponent>();
}

void ShootFireball::Enter()
{
}

State* ShootFireball::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);
    return nullptr;
}

void ShootFireball::Exit()
{
}
