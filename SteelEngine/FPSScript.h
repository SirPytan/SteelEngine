#pragma once
#include "SteelEnginePCH.h"
#include "BaseComponent.h"
#include "FPSComponent.h"
#include "TextRenderComponent.h"

using namespace dae;

class FPSComponent;
class TextRenderComponent;

class FPSScript : public BaseComponent
{
public:
	FPSScript();

	FPSScript(const FPSScript& other) = delete;
	FPSScript(FPSScript&& other) noexcept = delete;
	FPSScript& operator=(const FPSScript& other) = delete;
	FPSScript& operator=(FPSScript&& other) noexcept = delete;
	virtual ~FPSScript() = default;

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	FPSComponent* m_pFPSComponent = nullptr;
	TextRenderComponent* m_pTextRenderComponent = nullptr;
	float m_FPSRefreshInterval = 0.5f;
	float m_ElapsedTime = 0;
};

