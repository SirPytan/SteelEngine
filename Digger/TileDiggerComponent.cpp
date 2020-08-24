#include "SteelEnginePCH.h"
#include "TileDiggerComponent.h"
#include "SpriteComponent.h"
#include "TileInfo.h"
#include "Utils.h"

TileDiggerComponent::TileDiggerComponent(const std::vector<std::weak_ptr<GameObject>>& pTiles)
	: m_pTiles{pTiles}
{
}

void TileDiggerComponent::Initialize()
{
}

void TileDiggerComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	for (const auto& pTile : m_pTiles)
	{
		TileInfo* pTileInfo = pTile.lock()->GetComponent<TileInfo>();
		if (pTileInfo != nullptr)
		{
			Tile tile = pTileInfo->GetTile();
			if (tile.type != TileType::MoneyBag)
			{
				Elite::FPoint2 tileCenter = Elite::FPoint2(pTileInfo->GetCenterX(), pTileInfo->GetCenterY());
				Elite::FVector2 pos = GetGameObject()->GetPosition2D();
				pos.x += 20;
				pos.y -= 20;
				Elite::FPoint2 playerPos = Elite::FPoint2(pos);
				if (Elite::SqrDistance(tileCenter, playerPos) <= Elite::Square(m_MinDistance))
				{
					SpriteComponent* pSpriteComponent = pTile.lock()->GetComponent<SpriteComponent>();
					pSpriteComponent->SetAnimationParameters(AnimationType::OneFrame, 5, 5, true);

					if (tile.type == TileType::Emerald)
					{
						//Send Observer message for points
					}
				}
			}
		}
	}

}

void TileDiggerComponent::Render()
{
}
