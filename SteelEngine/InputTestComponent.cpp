#include "SteelEnginePCH.h"
#include "InputTestComponent.h"

using namespace SteelEngine;

InputTestComponent::InputTestComponent()
{
}

void InputTestComponent::Initialize()
{
	for (int i{}; i < 4; i++)
	{
		if (InputManager::GetInstance().IsControllerConnected(i))
		{
			m_ControllerId = i;
			break;
		}
	}
}

void InputTestComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	float triggerLeft = InputManager::GetInstance().GetTriggerValue(ControllerTrigger::Left, m_ControllerId);
	float triggerRight = InputManager::GetInstance().GetTriggerValue(ControllerTrigger::Right, m_ControllerId);
	if (triggerLeft > 0)
		std::cout << "TriggerLeft: " << triggerLeft << "\n";
	if (triggerRight > 0)
		std::cout << "TriggerRight: " << triggerRight << "\n";

	FVector4 stickLeft = InputManager::GetInstance().GetThumbStickDirectionAndMagnitude(ControllerStick::Left, m_ControllerId);
	FVector4 stickRight = InputManager::GetInstance().GetThumbStickDirectionAndMagnitude(ControllerStick::Right, m_ControllerId);

	if (stickLeft.z != 0.0f)
	{
		std::cout << "Left Stick:\n Magnitude: " << stickLeft.z << "\n Normalized Magnitude: " << stickLeft.w <<
		"\n Direction X: " << stickLeft.x << "\n Direction Y: " << stickLeft.y << "\n\n";
	}

	if (stickRight.z != 0.0f)
	{
		std::cout << "Right Stick:\n Magnitude: " << stickRight.z << "\n Normalized Magnitude: " << stickRight.w <<
			"\n Direction X: " << stickRight.x << "\n Direction Y: " << stickRight.y << "\n\n";
	}

	if (InputManager::GetInstance().IsPressed(ControllerButton::A, m_ControllerId))
	{
		std::cout << "Button Presssed\n";
		InputManager::GetInstance().SetRumble(m_ControllerId, 0.5f, 0.5f);
	}
	else
	{
		InputManager::GetInstance().SetRumble(m_ControllerId, 0.0f, 0.0f);
	}

}

void InputTestComponent::Render()
{
}
