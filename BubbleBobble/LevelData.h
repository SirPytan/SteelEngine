#pragma once
#include <vector>
#include "EnemyData.h"

struct TilePos
{
	TilePos(int xPos, int yPos)
		: x{xPos}
		, y{yPos}
	{}
	int x;
	int y;
};

struct LevelData
{
public:
	LevelData(unsigned int levelNumber) : m_LevelNumber{ levelNumber } {}
	void AddEnemy(const EnemyData& enemy) { m_Enemies.push_back(enemy); }
	void AddTilePos(const TilePos& tile){ m_TilePositions.push_back(tile); }
	void AddTilePos(int xPos, int yPos) { m_TilePositions.push_back(TilePos(xPos, yPos)); }
	std::vector<TilePos> GetTilePositions() const { return m_TilePositions; }
	std::vector<EnemyData> GetEnemies() const { return m_Enemies; }
	int GetLevelNumber() const { return m_LevelNumber; }
	unsigned int GetAmountOfEnemies() const { return (unsigned int)m_Enemies.size(); }

private:
	unsigned int m_LevelNumber{};
	std::vector<TilePos> m_TilePositions;
	std::vector<EnemyData> m_Enemies;
};

