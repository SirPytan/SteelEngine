#pragma once

enum class EnemyType : int
{
	Nobbin = 0,
	Hobbin = 1,
};

struct EnemyPos
{
	EnemyPos(int xPos, int yPos)
		: x{ xPos }
		, y{ yPos }
	{}
	int x;
	int y;
};

struct EnemyData
{
public:
	EnemyData(EnemyType type, EnemyPos pos)
		: type{type}
		, position{pos}
	{}

	EnemyType type;
	EnemyPos position;
};

