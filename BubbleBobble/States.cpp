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

    if (InputManager::GetInstance().IsPressed(ControllerButton::DpadLeft, m_pPlayerController->GetControllerId()))
    {
        return new WalkLeftState(m_pGameObject);
    }
    if (InputManager::GetInstance().IsPressed(ControllerButton::DpadRight, m_pPlayerController->GetControllerId()))
    {
        return new WalkRightState(m_pGameObject);
    }

    if (InputManager::GetInstance().IsPressed(ControllerButton::A, m_pPlayerController->GetControllerId()))
    {
        return new JumpState(m_pGameObject);
    }

    if (InputManager::GetInstance().IsPressed(ControllerButton::X, m_pPlayerController->GetControllerId()))
    {
        return new ShootBubble(m_pGameObject);
    }
    return nullptr;
}

void StandingState::Exit()
{
}
//-------------------------------------------------------------------


WalkLeftState::WalkLeftState(dae::GameObject* pGameObject)
    : State(pGameObject)
{
    m_pPlayerController = pGameObject->GetComponent<PlayerController>();
    m_pSprite = pGameObject->GetComponent<SpriteComponent>();
}

void WalkLeftState::Enter()
{
    m_pSprite->SetAnimationParameters(AnimationType::FromLeftToRight, 1, 2, false);
}

State* WalkLeftState::Update(float deltaTime)
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

void WalkLeftState::Exit()
{
}

//-------------------------------------------------------------------

WalkRightState::WalkRightState(dae::GameObject* pGameObject)
    : State(pGameObject)
{
    m_pPlayerController = pGameObject->GetComponent<PlayerController>();
    m_pSprite = pGameObject->GetComponent<SpriteComponent>();
}

void WalkRightState::Enter()
{
    m_pSprite->SetAnimationParameters(AnimationType::FromLeftToRight, 1, 1, false);
}

State* WalkRightState::Update(float deltaTime)
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

void WalkRightState::Exit()
{
}

//-------------------------------------------------------------------

JumpState::JumpState(dae::GameObject* pGameObject)
    : State(pGameObject)
{
    m_pPlayerController = pGameObject->GetComponent<PlayerController>();
    m_pSprite = pGameObject->GetComponent<SpriteComponent>();
}

void JumpState::Enter()
{
}

State* JumpState::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);
    return nullptr;
}

void JumpState::Exit()
{
}

//-------------------------------------------------------------------

ShootBubble::ShootBubble(dae::GameObject* pGameObject)
    : State(pGameObject)
{
    m_pPlayerController = pGameObject->GetComponent<PlayerController>();
    m_pSprite = pGameObject->GetComponent<SpriteComponent>();
}

void ShootBubble::Enter()
{
}

State* ShootBubble::Update(float deltaTime)
{
    UNREFERENCED_PARAMETER(deltaTime);
    return nullptr;
}

void ShootBubble::Exit()
{
}
