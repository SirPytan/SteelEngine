#include "SteelEnginePCH.h"
#include "ScoreObserver.h"

void ScoreObserver::Notify(dae::GameObject* gameObject, Event event)
{
	UNREFERENCED_PARAMETER(gameObject);

	if (event == Event::GotEmeralds)
	{
		m_Counter++;
		if (m_Counter == 8)
		{
			m_Score += 250;
			m_Counter = 0;
		}
		else
			m_Score += 25;

	}

	//Todo: if other points event, reset counter
}
