#pragma once
#include "BaseComponent.h"

class FPSComponent : public dae::BaseComponent 
{
public:
	FPSComponent();
	FPSComponent(const FPSComponent& other) = delete;
	FPSComponent(FPSComponent&& other) noexcept = delete;
	FPSComponent& operator=(const FPSComponent& other) = delete;
	FPSComponent& operator=(FPSComponent&& other) noexcept = delete;
	//~FPSComponent() override;
	int GetFPS() { return (int)m_FPS; }
	void SetActive(bool active) { m_Active = active; }

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	float m_Active = true;
	float m_FPSTimer = 0.f;
	float m_FPSCounter = 0;
	float m_FPS = 0;
};

