#include "SteelEnginePCH.h"
#include "DiggerGame.h"

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
#include "PlayerController.h"

DiggerGame::DiggerGame()
	: SteelEngineGame("Digger - by 2DAE02_Patyk_Daniel - Prog4")
{
}

void DiggerGame::Initialize()
{
	LevelReader levelReader{"Levels2.txt"};
	levelReader.ReadLevels();

	Scene* pScene = SceneManager::GetInstance().CreateScene("Game");

	//Input Test-------------------------------------------------------------
	//auto go = std::make_shared<GameObject>();
	//InputTestComponent* pInputTest = new InputTestComponent();
	//go->AddComponent(pInputTest);
	//pScene->Add(go);


	//Level----------------------------------------------------------------------------------
	std::vector<std::weak_ptr<GameObject>> pDynamicObjects{};
	int level = 1;
	int playerSpawnX{};
	int playerSpawnY{};
	int enemySpawnX{};
	int enemySpawnY{};
	int tileSize = 40;

	auto texture = ResourceManager::GetInstance().LoadTexture("Spritesheet.png");
	for (Tile tile : levelReader.GetLevel(level-1).GetTilePositions())
	{
		auto levelTile = std::make_shared<GameObject>();
		SpriteComponent* pLevelSprite = new SpriteComponent(texture, 8, 8, 1, 1);
		switch (tile.type)
		{
		case TileType::Wall:
			pLevelSprite->SetAnimationParameters(AnimationType::OneFrame, level, 1, true);
			break;
		case TileType::H_Tunnel:
			pLevelSprite->SetAnimationParameters(AnimationType::OneFrame, 5, 5, true);
			break;
		case TileType::V_Tunnel:
			pLevelSprite->SetAnimationParameters(AnimationType::OneFrame, 5, 5, true);
			break;
		case TileType::MoneyBag:
			pLevelSprite->SetAnimationParameters(AnimationType::OneFrame, level, 3, true);
			break;
		case TileType::Emerald:
			pLevelSprite->SetAnimationParameters(AnimationType::OneFrame, level, 2, true);
			break;
		case TileType::PlayerSpawn:
			pLevelSprite->SetAnimationParameters(AnimationType::OneFrame, 5, 5, true);
			playerSpawnX = tile.x * tileSize;
			playerSpawnY = tile.y * tileSize;
			break;
		case TileType::EnemySpawn:
			pLevelSprite->SetAnimationParameters(AnimationType::OneFrame, 5, 5, true);
			enemySpawnX = tile.x * tileSize;
			enemySpawnY = tile.y * tileSize;
			break;
		}
		pLevelSprite->SetDestinationRectPosition(tile.x * tileSize, tile.y * tileSize);
		BoxCollider2D* pBoxCollider = new BoxCollider2D(&pDynamicObjects, pLevelSprite->GetDestinationRect());
		levelTile->AddComponent(pLevelSprite);
		levelTile->AddComponent(pBoxCollider);
		pScene->Add(levelTile);
	}

	//Bottom Border------------------------------------------------------------------------------
	auto bottomborder = std::make_shared<GameObject>();
	for (int i{}; i < 15; i++)
	{
		SpriteComponent* pBorderSprite = new SpriteComponent(texture, 8, 8, 1, 1);
		pBorderSprite->SetAnimationParameters(AnimationType::OneFrame, 8, 8, true);
		pBorderSprite->SetDestinationRectPosition(i * tileSize, 10 * tileSize);
		bottomborder->AddComponent(pBorderSprite);
	}
	pScene->Add(bottomborder);

	//Player--------------------------------------------------------------------------------------
	auto player = std::make_shared<GameObject>();
	player->SetPosition((float)playerSpawnX,(float)playerSpawnY);
	SpriteComponent* pSprite = new SpriteComponent("Spritesheet.png", 8, 8, 1, 1);
	pSprite->SetAnimationParameters(AnimationType::OneFrame, 1, 4, false);
	pSprite->SetDestinationRectPosition((int)player->GetPosition().x, (int)player->GetPosition().y);
	player->AddComponent(pSprite);

	//Todo: Make collision rect smaller
	BoxCollider2D* pPlayerBoxCollider = new BoxCollider2D(&pDynamicObjects, pSprite->GetDestinationRect(), false);
	player->AddComponent(pPlayerBoxCollider);
	//Todo: Add Player Controller
	//Todo: Add Correct State behavior
	//Todo: Remove Tiles if touched.


	pScene->Add(player);
	//--------------------------------------------------------------------------------------------


	//auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	//auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	//to->SetPosition(80, 20);
	//pScene->Add(to);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto fpsObject = std::make_shared<GameObject>();
	FPSComponent* pFPSComponent = new FPSComponent();
	TextRenderComponent* pTextRender = new TextRenderComponent(font);
	FPSScript* pFPSScript = new FPSScript();
	pTextRender->SetColor({ 255,255,0 });
	fpsObject->AddComponent(pFPSComponent);
	fpsObject->AddComponent(pTextRender);
	fpsObject->AddComponent(pFPSScript);
	fpsObject->SetPosition(10, 10);
	pScene->Add(go);
	SceneManager::GetInstance().SetActivScene(pScene);
}
