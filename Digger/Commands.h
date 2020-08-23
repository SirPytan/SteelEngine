#pragma once
//#ifndef COMMANDS
//#define COMMANDS

#include "Command.h"
#include "GameObject.h"

using namespace dae;

class MoveLeft : public Command
{
public:
	MoveLeft(int controllerId, GameObject* pPlayer);
	~MoveLeft() = default;
	void Execute() override;
};

class MoveRight : public Command
{
public:
	MoveRight(int controllerId, GameObject* pPlayer);
	~MoveRight() = default;
	void Execute() override;
};

class MoveUp : public Command
{
public:
	MoveUp(int controllerId, GameObject* pPlayer);
	~MoveUp() = default;
	void Execute() override;
};

class MoveDown : public Command
{
public:
	MoveDown(int controllerId, GameObject* pPlayer);
	~MoveDown() = default;
	void Execute() override;
};

class ShootFireball : public Command
{
public:
	ShootFireball(int controllerId, GameObject* pPlayer);
	~ShootFireball() = default;
	void Execute() override;
};

//#endif

