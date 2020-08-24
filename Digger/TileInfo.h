#pragma once
#include <BaseComponent.h>
#include "LevelData.h"
class TileInfo : public dae::BaseComponent
{
public:
	TileInfo(Tile tile, float centerX, float centerY);
	~TileInfo() = default;

	TileInfo(const TileInfo& other) = delete;
	TileInfo(TileInfo&& other) noexcept = delete;
	TileInfo& operator=(const TileInfo& other) = delete;
	TileInfo& operator=(TileInfo&& other) noexcept = delete;

	Tile GetTile() { return m_Tile; }
	float GetCenterX() { return m_CenterX; }
	float GetCenterY() { return m_CenterY; }

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
private:
	Tile m_Tile;
	float m_CenterX{};
	float m_CenterY{};

};

