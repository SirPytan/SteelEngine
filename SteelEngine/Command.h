#pragma once
//#include "GameObject.h"
#include "SteelEngineStructs.h"

class Command
{
public:
	Command() = default;
	Command(int controllerId) : m_ControllerId{controllerId}{}
	virtual ~Command() = default;
	virtual void Execute(/*GameObject& gameObject*/) = 0;
	void SetControllerId(int controllerId) { m_ControllerId = controllerId; }
	int GetControllerId() const { return m_ControllerId; }
protected:
	int m_ControllerId = 0;
	Input* m_Input = nullptr;
};