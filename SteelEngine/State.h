#pragma once
#include "GameObject.h"
#include <memory>

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

//class StandingState : public State
//{
//public:
//	StandingState(dae::GameObject* pGameObject);
//	~StandingState() override;
//	void Enter() override;
//	State* Update(float deltaTime) override;
//	void Exit() override;
//
//
//private:
//
//};
