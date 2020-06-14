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
#include "SpriteComponent.h"
#include "LevelReader.h"
#include "BoxCollider2D.h"

BubbleBobbleGame::BubbleBobbleGame()
	: SteelEngineGame("BubbleBobble - by 2DAE02_Patyk_Daniel - Prog4")
{
}

void BubbleBobbleGame::Initialize()
{
	LevelReader levelReader{};
	levelReader.ReadLevels();
	levelReader.ReadEnemies();

	Scene* pScene = SceneManager::GetInstance().CreateScene("Game");

	auto go = std::make_shared<GameObject>();
	InputTestComponent* pInputTest = new InputTestComponent();
	go->AddComponent(pInputTest);
	pScene->Add(go);

	//Player--------------------------------------------------------------------------------------
	//Sprites0

	auto player = std::make_shared<GameObject>();
	player->SetPosition(200, 180);
	SpriteComponent* pSprite = new SpriteComponent("Sprites0_slim.png", 8, 16, 8, 1);
	pSprite->SetAnimationParameters(AnimationType::FromLeftToRight, 1, 1, false);
	pSprite->SetDestinationRectPosition((int)player->GetPosition().x, (int)player->GetPosition().y);
	player->AddComponent(pSprite);

	BoxCollider2D* pPlayerBoxCollider = new BoxCollider2D(std::vector<std::weak_ptr<GameObject>>(), pSprite->GetDestinationRect(), false);
	player->AddComponent(pPlayerBoxCollider);

	pScene->Add(player);
	//--------------------------------------------------------------------------------------------

	std::vector<std::weak_ptr<GameObject>> dynamicObject{};
	dynamicObject.push_back(player);

	auto level = std::make_shared<GameObject>();
	auto texture = ResourceManager::GetInstance().LoadTexture("BigTiles.png");
	for (TilePos tile : levelReader.GetLevel(0).GetTilePositions())
	{
		SpriteComponent* pSprite = new SpriteComponent(texture, 10, 10, 1, 1);
		pSprite->SetAnimationParameters(AnimationType::OneFrame, 1, 1, true);
		pSprite->SetDestinationRectPosition(tile.x * 16, (tile.y * 16));
		BoxCollider2D* pBoxCollider = new BoxCollider2D(dynamicObject, pSprite->GetDestinationRect());
		level->AddComponent(pSprite);
		level->AddComponent(pBoxCollider);
	}
	pScene->Add(level);




	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//pScene->Add(to);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	go = std::make_shared<GameObject>();
	FPSComponent* pFPSComponent = new FPSComponent();
	TextRenderComponent* pTextRender = new TextRenderComponent(font);
	FPSScript* pFPSScript = new FPSScript();
	pTextRender->SetColor({ 255,255,0 });
	go->AddComponent(pFPSComponent);
	go->AddComponent(pTextRender);
	go->AddComponent(pFPSScript);
	go->SetPosition(10, 10);
	pScene->Add(go);
	SceneManager::GetInstance().SetActivScene(pScene);
}
