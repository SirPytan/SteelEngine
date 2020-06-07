#include "SteelEnginePCH.h"
#include "InputManager.h"
#include <SDL.h>

//Source:
//https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput#multiple-controllers

void dae::InputManager::Initialize()
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

bool dae::InputManager::ProcessInput()
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





bool dae::InputManager::IsPressed(ControllerButton button,int controllerId) const
{
	if (m_XInputStates[controllerId].first)
	{
		switch (button)
		{
		case ControllerButton::ButtonA:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_A;
		case ControllerButton::ButtonB:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_B;
		case ControllerButton::ButtonX:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_X;
		case ControllerButton::ButtonY:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
		case ControllerButton::ButtonDpadUp:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
		case ControllerButton::ButtonDpadDown:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
		case ControllerButton::ButtonDpadLeft:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
		case ControllerButton::ButtonDpadRight:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
		case ControllerButton::ButtonStart:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_START;
		case ControllerButton::ButtonBack:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
		case ControllerButton::ButtonLeftThumb:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
		case ControllerButton::ButtonRightThumb:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
		case ControllerButton::ButtonLeftShoulder:
			return m_XInputStates[controllerId].second.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
		case ControllerButton::ButtonRightShoulder:
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

