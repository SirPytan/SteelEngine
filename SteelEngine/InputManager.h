#pragma once
#include <XInput.h>
#include "Singleton.h"

//Intial design from the DAE did not support multiple controllers and only the buttons A,B,X,Y
//Extended by Daniel Patyk: Added multiple controller support, all buttons, triggers and sticks.

namespace dae
{
	enum class ControllerButton : int
	{
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonDpadUp = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDpadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonDpadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonDpadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonBack = XINPUT_GAMEPAD_BACK,
		ButtonLeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		ButtonRightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		ButtonLeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		ButtonRightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void Initialize();
		bool ProcessInput();
		bool IsPressed(ControllerButton button, int controllerId) const;
	
		bool IsControllerConnected(int controllerId) { return m_XInputStates[controllerId].first; }
	private:
		//Bool indicates if a controller is connected or not
		 std::pair<bool, XINPUT_STATE> m_XInputStates[4]{};

	};

}
