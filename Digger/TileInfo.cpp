#include "SteelEnginePCH.h"
#include "TileInfo.h"

TileInfo::TileInfo(Tile tile, float centerX, float centerY)
	: m_Tile{tile}
	, m_CenterX{centerX}
	, m_CenterY{centerY}
{
}

void TileInfo::Initialize()
{
}

void TileInfo::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TileInfo::Render()
{
}
