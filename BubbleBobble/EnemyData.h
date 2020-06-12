#pragma once

enum class EnemyType : int
{
	ZenChan = 0,
	Mighta = 1,
	Monsta = 2,
	Pulpul = 3,
	Banebou = 4,
	Hidegons = 5,
	Drunk = 6, 
	Invader = 7
};

enum class Direction : int
{
	Left = 0,
	Right = 1
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
	EnemyData(EnemyType type, EnemyPos pos,  Direction dir, float delay)
		: type{type}
		, position{pos}
		, direction{dir}
		, delay{delay}
	{}

	EnemyType type;
	EnemyPos position;
	Direction direction;
	float delay{};
};

