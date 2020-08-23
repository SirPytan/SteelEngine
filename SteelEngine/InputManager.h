#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "EMath.h"
#include <map>
#include "Command.h"

//Intial design from the DAE did not support multiple controllers and only the buttons A,B,X,Y
//Extended by Daniel Patyk: Added multiple controller support, all buttons, triggers and sticks.

using namespace Elite;
using namespace dae;

namespace SteelEngine
{
	enum class ControllerButton : int
	{
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
		DpadUp = XINPUT_GAMEPAD_DPAD_UP,
		DpadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		DpadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		DpadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK,
		LeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		RightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		LeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER
	};

	enum class ControllerStick : int
	{
		Left = 0,
		Right = 1
	};

	enum class ControllerTrigger : int
	{
		Left = 0,
		Right = 1
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Initialize();
		bool ProcessInput();
		bool IsPressed(ControllerButton button, int controllerId) const;
		//Direction is normalized between -1.0 and 1.0
		//x = X Direction, y = Y Direction, z = Magnitude, w = NormalizedMagnitude
		FVector4 GetThumbStickDirectionAndMagnitude(ControllerStick stick, int controllerId) const;
		//Returns values between 0.0 and 1.0
		float GetTriggerValue(ControllerTrigger trigger, int controllerId) const;
		bool IsControllerConnected(int controllerId) { return m_XInputStates[controllerId].first; }
		//Left and Right take float values between 0.0 (Min) and 1.0 (Max)
		void SetRumble(int controllerId, float left, float right) const;

		bool AddCommand(Command* pCommand, ControllerButton button);
	private:
		//Bool indicates if a controller is connected or not
		 std::pair<bool, XINPUT_STATE> m_XInputStates[4]{};
		 std::map<ControllerButton, Command*> m_Commands;
	};

}
