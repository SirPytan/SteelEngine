#pragma once
#ifndef OBSERVER
#define OBSERVER

#include "Enums.h"
#include "GameObject.h"
using namespace dae;

class GameObject;

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Notify(dae::GameObject* gameObject, Event event) = 0;
};
#endif

