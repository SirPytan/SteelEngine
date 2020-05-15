#pragma once
#include <string>

struct SDL_Window;

class SteelEngineGame
{
public:
	SteelEngineGame(const SteelEngineGame& other) = delete;
	SteelEngineGame(SteelEngineGame&& other) noexcept = delete;
	SteelEngineGame& operator=(const SteelEngineGame& other) = delete;
	SteelEngineGame& operator=(SteelEngineGame&& other) noexcept = delete;
	SteelEngineGame(std::string gameName);
	virtual ~SteelEngineGame();

	void Run();

protected:
	virtual void Initialize() = 0;
private:
	//FUNCTIONS
	//Initializations
	void InitializeWindow(std::string windowTitle, int winWidth, int winHeight);
	void InitializeGame();
	void Cleanup();

	//Member
	std::string m_GameName;
	SDL_Window* m_Window{};
};

