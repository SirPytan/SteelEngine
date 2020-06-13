#pragma once
class Command
{
public:
	Command() = default;
	Command(int controllerId) : m_ControllerId{controllerId}{}
	virtual ~Command() = default;
	virtual void Execute() = 0;
	void SetControllerId(int controllerId) { m_ControllerId = controllerId; }
	int GetControllerId() const { return m_ControllerId; }
protected:
	int m_ControllerId = 0;
};