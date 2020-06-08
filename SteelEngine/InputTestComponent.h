#pragma once
#include "BaseComponent.h"
#include "InputManager.h"

class InputTestComponent : public dae::BaseComponent
{
public:
	InputTestComponent();
	InputTestComponent(const InputTestComponent& other) = delete;
	InputTestComponent(InputTestComponent&& other) noexcept = delete;
	InputTestComponent& operator=(const InputTestComponent& other) = delete;
	InputTestComponent& operator=(InputTestComponent&& other) noexcept = delete;
	//~InputTestComponent() override;

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	int m_ControllerId{};
};

