#pragma once
#include "SteelEnginePCH.h"
#include "SteelEngineGame.h"
#include "SceneManager.h"
#include <chrono>
#include <thread>
#include <SDL.h>
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputManager.h"

using namespace std;
using namespace std::chrono;
using namespace dae;
using namespace SteelEngine;

SteelEngineGame::SteelEngineGame(std::string gameName)
	: m_GameName(gameName)
{}

SteelEngineGame::~SteelEngineGame()
{}

void SteelEngineGame::Run()
{
	srand(unsigned int(time(nullptr)));
	InitializeWindow(m_GameName, 640, 480);
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	InitializeGame();

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;
	float secondsPerUpdate = 0.02f;
	bool doContinue = true;

	sceneManager.Initialize();
	while (doContinue)
	{
		const auto currentTime = high_resolution_clock::now();
		float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;
		doContinue = input.ProcessInput();
		while (lag >= secondsPerUpdate)
		{
			sceneManager.FixedUpdate();
			lag -= secondsPerUpdate;
		}
		sceneManager.Update(deltaTime);
		renderer.Render();
	}

	Cleanup();
}

void SteelEngineGame::InitializeWindow(std::string windowTitle, int winWidth, int winHeight)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow
	(
		windowTitle.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		winWidth,
		winHeight,
		SDL_WINDOW_OPENGL
	);

	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

}

void SteelEngineGame::InitializeGame()
{
	//Space for additional Game Engine Initalizations
	InputManager::GetInstance().Initialize();
	//Game Initialize
	Initialize();
}

void SteelEngineGame::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SceneManager::GetInstance().Cleanup();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}
