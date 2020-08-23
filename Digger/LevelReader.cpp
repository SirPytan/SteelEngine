#include "LevelReader.h"
#include <type_traits>
#include <iostream>
#include <fstream>
#include <regex>


LevelReader::LevelReader(std::string filename)
	: m_LevelFilename{filename}
{
}

bool LevelReader::ReadLevels()
{
	std::ifstream inputStream(m_DataPath + m_LevelFilename, std::ios::in | std::ios::binary);
	if (!inputStream)
	{
		std::cerr << "Cannot open " << m_LevelFilename << std::endl;
		return false;
	}
	else
	{
		std::regex regexLevelNo("^(LV)(\\d)(\\s*)$");
		std::smatch matches;
		unsigned int row{};
		unsigned int column{};
		std::string line;
		LevelData* level = nullptr;

		if (inputStream.is_open())
		{
			while (std::getline(inputStream, line))
			{

				if (line == "")
					continue;
				
				if (std::regex_search(line, matches, regexLevelNo))
				{
					if (matches[1].str() == "LV")
					{
						if (level != nullptr)
						{
							m_Levels.push_back(*level);
						}
						level = new LevelData(std::stoi(matches[2].str()));
						row = 0;
						column = 0;
					}
				}
				else
				{
					for (const char& c : line)
					{
						switch (c)
						{
						case 'P':
							level->AddTilePos(column, row, TileType::PlayerSpawn);
							break;
						case 'S':
							level->AddTilePos(column, row, TileType::EnemySpawn);
							break;
						case 'H':
							level->AddTilePos(column, row, TileType::H_Tunnel);
							break;
						case 'V':
							level->AddTilePos(column, row, TileType::V_Tunnel);
							break;
						case 'B':
							level->AddTilePos(column, row, TileType::MoneyBag);
							break;
						case 'C':
							level->AddTilePos(column, row, TileType::Emerald);
							break;
						case '#':
							level->AddTilePos(column, row, TileType::Wall);
							break;
						}
						column++;
					}
					column = 0;
					row++;
				}
			}
			inputStream.close();
		}
	}

	return true;
}
