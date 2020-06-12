#pragma once
#include <vector>
#include "BinaryReader.h"
#include "LevelData.h"
#include "EnemyData.h"

class LevelReader
{
public:
	LevelReader();
	bool ReadLevels();
	bool ReadEnemies();

private:
	const std::string m_DataPath = "../Data/";
	std::vector<LevelData> m_Levels;
	unsigned char m_LevelBitmask[8]{};
	std::uint_fast8_t m_EnemyBitmask[8]{};
	EnemyType m_EnemyTypes[8]{};
	const std::uint_fast8_t m_ZeroBitmask = 0b00000000;
	const std::uint_fast8_t m_EnemyTypeMask = 0b00000111;
	const std::uint_fast8_t m_ColumnAndRowMask = 0b11111000;
	const std::uint_fast8_t m_DelayMask = 0b00111111;
	const std::uint_fast8_t m_DirectionMask = 0b11000000;
	const float m_ApproxTimePerFrame = 0.017f;
};

