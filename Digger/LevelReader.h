#pragma once
#include <string>
#include <vector>
#include "LevelData.h"

class LevelReader
{
public:
	LevelReader(std::string filename);
	bool ReadLevels();
	std::vector<LevelData> GetLevels() const { return m_Levels; }
	LevelData GetLevel(unsigned int index) const { return m_Levels[index]; }

private:
	std::string m_LevelFilename{};
	const std::string m_DataPath = "../Data/";
	std::vector<LevelData> m_Levels;
};

