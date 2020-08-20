#pragma once
#include "SteelEngineGame.h"

class DiggerGame : public SteelEngineGame
{
public:
	DiggerGame();
	~DiggerGame() = default;
protected:
	void Initialize() override;
};

