#include "SteelEnginePCH.h"
#include "InputManager.h"
#include <SDL.h>

//Source:
//https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput#multiple-controllers

void SteelEngine::InputManager::Initialize()
{
	//Checking which controller are connected
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_XInputStates[i].second, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &m_XInputStates[i].second);

		if (dwResult == ERROR_SUCCESS)
		{
			//Controller is connected
			m_XInputStates[i].first = true;
		}
		else
		{
			//Controller is not connected
			m_XInputStates[i].first = false;
		}
	}
}

bool SteelEngine::InputManager::ProcessInput()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		ZeroMemory(&m_XInputStates[i].second, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &m_XInputStates[i].second);

		if (dwResult == ERROR_SUCCESS)
		{
			//Controller is connected
			m_XInputStates[i].first = true;
		}
		else
		{
			//Controller is not connected
			m_XInputStates[i].first = false;
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || e.type == SDL_SCANCODE_ESCAPE)
		{
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			
		}
	}

	return true;
}


bool SteelEngine::InputManager::IsPressed(ControllerButton button,int controllerId) const
{
	if (m_XInputStates[controllerId].first)
	{
		switch (button)
		{
		case ControllerButton::A:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_A;
		case ControllerButton::B:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_B;
		case ControllerButton::X:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_X;
		case ControllerButton::Y:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
		case ControllerButton::DpadUp:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		case ControllerButton::DpadDown:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		case ControllerButton::DpadLeft:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		case ControllerButton::DpadRight:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		case ControllerButton::Start:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_START;
		case ControllerButton::Back:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
		case ControllerButton::LeftThumb:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
		case ControllerButton::RightThumb:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
		case ControllerButton::LeftShoulder:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		case ControllerButton::RightShoulder:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
		default: return false;
		}
	}
	else
	{
		std::cout << "Controller with ID: " << controllerId << " was not connected. Could not handle IsPressed(). Returning false.\n";
		return false;
	}
}

FVector4 SteelEngine::InputManager::GetThumbStickDirectionAndMagnitude(ControllerStick stick, int controllerId) const
{
	FVector2 stickValues{};
	FVector2 stickDirection{};
	int deadzone{};

	switch (stick)
	{
	case SteelEngine::ControllerStick::Left:
		stickValues.x = m_XInputStates[controllerId].second.Gamepad.sThumbLX;
		stickValues.y = m_XInputStates[controllerId].second.Gamepad.sThumbLY;
		deadzone = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		break;
	case SteelEngine::ControllerStick::Right:
		stickValues.x = m_XInputStates[controllerId].second.Gamepad.sThumbRX;
		stickValues.y = m_XInputStates[controllerId].second.Gamepad.sThumbRY;
		deadzone = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
		break;
	default:
		std::cout << "No valid enum\n";
		return FVector4();
		break;
	}


	//determine how far the controller is pushed
	float magnitude = sqrt(stickValues.x * stickValues.x + stickValues.y * stickValues.y);

	//determine the direction the controller is pushed
	stickDirection.x = stickValues.x / magnitude;
	stickDirection.y = stickValues.y / magnitude;

	float normalizedMagnitude = 0;

	FVector4 stickDirectionAndMagnitude{};


	//check if the controller is outside a circular dead zone
	if (magnitude > deadzone)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= deadzone;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - deadzone);

		stickDirectionAndMagnitude.x = stickDirection.x;
		stickDirectionAndMagnitude.y = stickDirection.y;
		stickDirectionAndMagnitude.z = magnitude;
		stickDirectionAndMagnitude.w = normalizedMagnitude;

	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0f;
		normalizedMagnitude = 0.0f;

		stickDirectionAndMagnitude.x = 0.0f;
		stickDirectionAndMagnitude.y = 0.0f;
		stickDirectionAndMagnitude.z = magnitude;
		stickDirectionAndMagnitude.w = normalizedMagnitude;
	}

	return stickDirectionAndMagnitude; //Direction is normalized
}

float SteelEngine::InputManager::GetTriggerValue(ControllerTrigger trigger, int controllerId) const
{
	float triggerValue{};

	switch (trigger)
	{
	case SteelEngine::ControllerTrigger::Left:
		triggerValue = m_XInputStates[controllerId].second.Gamepad.bLeftTrigger; //The value is between 0 and 255
		break;
	case SteelEngine::ControllerTrigger::Right:
		triggerValue = m_XInputStates[controllerId].second.Gamepad.bRightTrigger;
		break;
	default:
		std::cout << "No valid enum\n";
		return 0.0f;
		break;
	}

	if (triggerValue > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return triggerValue / 255.f;
	else
		return 0.0f;
}

//Maybe put this in a rumble manager, if it needs more functionality
void SteelEngine::InputManager::SetRumble(int controllerId, float left, float right) const
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = (WORD)(Clamp((int)(left*65535), 0, 65535)); // use any value between 0-65535 here
	vibration.wRightMotorSpeed = (WORD)(Clamp((int)(right * 65535), 0, 65535)); // use any value between 0-65535 here
	XInputSetState((DWORD)controllerId, &vibration);
}

