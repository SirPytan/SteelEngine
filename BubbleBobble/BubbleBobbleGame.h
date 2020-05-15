#pragma once
#include "SteelEngineGame.h"

class BubbleBobbleGame : public SteelEngineGame
{
public:
	BubbleBobbleGame();
	~BubbleBobbleGame() = default;
protected:
	void Initialize() override;
};

