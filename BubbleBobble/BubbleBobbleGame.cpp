#include "SteelEnginePCH.h"
#include "BubbleBobbleGame.h"

#include "SceneManager.h"
#include "ResourceManager.h"
#include "FPSComponent.h"
#include "TextRenderComponent.h"
#include "FPSScript.h"
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Transform.h"
#include "InputTestComponent.h"

BubbleBobbleGame::BubbleBobbleGame()
	: SteelEngineGame("BubbleBobble - by 2DAE02_Patyk_Daniel - Prog4")
{
}

void BubbleBobbleGame::Initialize()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	InputTestComponent* pInputTest = new InputTestComponent();
	go->AddComponent(pInputTest);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	go = std::make_shared<GameObject>();
	FPSComponent* pFPSComponent = new FPSComponent();
	TextRenderComponent* pTextRender = new TextRenderComponent(font);
	FPSScript* pFPSScript = new FPSScript();
	pTextRender->SetColor({ 255,255,0 });
	go->AddComponent(pFPSComponent);
	go->AddComponent(pTextRender);
	go->AddComponent(pFPSScript);
	go->SetPosition(10, 10);
	scene.Add(go);
}
