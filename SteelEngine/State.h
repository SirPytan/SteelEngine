#pragma once
#include "SteelEnginePCH.h"
#include "GameObject.h"

class State
{
public:
	State(dae::GameObject* pGameObject) : m_pGameObject{pGameObject} {};
	virtual ~State() { m_pGameObject = nullptr; }
	virtual void Enter() = 0;
	virtual State* Update(float deltaTime) = 0;
	virtual void Exit() = 0;
protected:
	dae::GameObject* m_pGameObject = nullptr;
};

