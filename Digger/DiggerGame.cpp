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
#include "TileInfo.h"
#include "TileDiggerComponent.h"
#include "ScoreObserver.h"
#include "ScoreScriptComponent.h"

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
	//std::vector<std::weak_ptr<GameObject>> pDynamicObjects{};
	int level = 1;
	int playerSpawnX{};
	int playerSpawnY{};
	int enemySpawnX{};
	int enemySpawnY{};
	int tileSize = 40;

	std::vector<std::weak_ptr<dae::GameObject>> tiles{};

	auto texture = ResourceManager::GetInstance().LoadTexture("Spritesheet.png");
	for (Tile tile : levelReader.GetLevel(level - 1)->GetTilePositions())
	{
		auto levelTile = std::make_shared<dae::GameObject>();
		SpriteComponent* pLevelSprite = new SpriteComponent(texture, 8, 8, 1, 1);
		TileInfo* pTileInfo = new TileInfo(tile, (tile.x * tileSize) + (tileSize * 0.5f), (tile.y * tileSize) - (tileSize * 0.5f));
		levelTile->AddComponent(pTileInfo);
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
		levelTile->AddComponent(pLevelSprite);
		//BoxCollider2D* pBoxCollider = new BoxCollider2D(&pDynamicObjects, pLevelSprite->GetDestinationRect());
		//levelTile->AddComponent(pBoxCollider);
		tiles.push_back(levelTile);
		pScene->Add(levelTile);
	}

	//Bottom Border------------------------------------------------------------------------------
	auto bottomborder = std::make_shared<dae::GameObject>();
	for (int i{}; i < 15; i++)
	{
		SpriteComponent* pBorderSprite = new SpriteComponent(texture, 8, 8, 1, 1);
		pBorderSprite->SetAnimationParameters(AnimationType::OneFrame, 8, 8, true);
		pBorderSprite->SetDestinationRectPosition(i * tileSize, 10 * tileSize);
		bottomborder->AddComponent(pBorderSprite);
	}
	pScene->Add(bottomborder);

	//Player--------------------------------------------------------------------------------------
	auto player = std::make_shared<dae::GameObject>();
	player->SetPosition((float)playerSpawnX,(float)playerSpawnY);
	SpriteComponent* pSprite = new SpriteComponent("Spritesheet.png", 8, 8, 1, 1);
	pSprite->SetAnimationParameters(AnimationType::OneFrame, 1, 4, false);
	pSprite->SetDestinationRectPosition((int)player->GetPosition().x, (int)player->GetPosition().y);
	player->AddComponent(pSprite);

		PlayerController* pPlayerController = new PlayerController(PlayerNumber::P1);
	player->AddComponent(pPlayerController);

	ScoreObserver* pScoreObserver = new ScoreObserver();

	TileDiggerComponent* pTileDigger = new TileDiggerComponent(tiles);
	pTileDigger->AddObserver(pScoreObserver);
	player->AddComponent(pTileDigger);
	pScene->Add(player);
	//--------------------------------------------------------------------------------------------
	//Score
	auto scoreFont = ResourceManager::GetInstance().LoadFont("Pixellari.otf", 15);
	auto scoreObject = std::make_shared<dae::GameObject>();
	TextRenderComponent* pScoreTextRender = new TextRenderComponent(scoreFont);
	ScoreScriptComponent* pScoreScriptComponent = new ScoreScriptComponent(pScoreObserver);
	pScoreTextRender->SetColor({ 0,255,0 });
	scoreObject->AddComponent(pScoreTextRender);
	scoreObject->AddComponent(pScoreScriptComponent);
	scoreObject->SetPosition(10, 460);
	pScene->Add(scoreObject);


	
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	auto fpsObject = std::make_shared<dae::GameObject>();
	FPSComponent* pFPSComponent = new FPSComponent();
	TextRenderComponent* pTextRender = new TextRenderComponent(font);
	FPSScript* pFPSScript = new FPSScript();
	pTextRender->SetColor({ 255,255,0 });
	fpsObject->AddComponent(pFPSComponent);
	fpsObject->AddComponent(pTextRender);
	fpsObject->AddComponent(pFPSScript);
	fpsObject->SetPosition(10, 10);
	pScene->Add(fpsObject);


	SceneManager::GetInstance().SetActivScene(pScene);
	
}
