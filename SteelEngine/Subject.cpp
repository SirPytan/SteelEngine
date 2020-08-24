#include "SteelEnginePCH.h"
#include "Subject.h"
#include "Helpers.h"

void Subject::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
	m_Observers.erase(std::find(m_Observers.begin(), m_Observers.end(), observer));
}

void Subject::RemoveAllObservers()
{
	m_Observers.erase(m_Observers.begin(), m_Observers.end());
}

void Subject::DeleteAllObservers()
{
	for (Observer* pObserver : m_Observers)
	{
		SafeDelete(pObserver);
	}
	RemoveAllObservers();
}

void Subject::Notify(dae::GameObject* caller, Event event)
{
	for (Observer* observer : m_Observers)
		observer->Notify(caller, event);
}
