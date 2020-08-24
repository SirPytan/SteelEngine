#pragma once
#include "Observer.h"
#include "GameObject.h"
class ScoreObserver : public Observer
{
	void Notify(dae::GameObject* gameObject, Event event) override;
	int GetScore() { return m_Score; }

private:
	int m_Score{};
	int m_Counter{};

};

