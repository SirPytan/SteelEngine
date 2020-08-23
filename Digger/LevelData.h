#pragma once
#include <vector>
#include "EnemyData.h"

enum class TileType
{
	Wall, H_Tunnel, V_Tunnel, MoneyBag, Emerald, PlayerSpawn, EnemySpawn
};

struct Tile
{
	Tile(int xPos, int yPos, TileType type)
		: x{xPos}
		, y{yPos}
		, type{type}
	{}
	int x;
	int y;

	TileType type;
};

struct LevelData
{
public:
	LevelData() = default;
	LevelData(unsigned int levelNumber) : m_LevelNumber{ levelNumber } {}
	void AddTilePos(const Tile& tile){ m_TilePositions.push_back(tile); }
	void AddTilePos(int xPos, int yPos, TileType type) { m_TilePositions.push_back(Tile(xPos, yPos, type)); }
	std::vector<Tile> GetTilePositions() const { return m_TilePositions; }
	unsigned int GetLevelNumber() const { return m_LevelNumber; }
	void SetLevelNumber(unsigned int levelNumber) { m_LevelNumber = levelNumber; }

private:
	unsigned int m_LevelNumber{};
	std::vector<Tile> m_TilePositions{};
};

