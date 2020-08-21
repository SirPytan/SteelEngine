#pragma once
#ifndef SUBJECT
#define SUBJECT

#include <vector>
#include "GameObject.h"
#include "Observer.h"
#include "Enums.h"

using namespace dae;
class GameObject;
class Observer;

class Subject
{
public:
	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);
	void Notify(dae::GameObject* caller, Event event);

private:
	std::vector<Observer*> m_Observers{};
};

#endif