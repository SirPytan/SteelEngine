#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "FPSComponent.h"
#include "TextRenderComponent.h"
#include "FPSScript.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 15);
	go = std::make_shared<GameObject>();
	FPSComponent* pFPSComponent = new FPSComponent();
	TextRenderComponent* pTextRender = new TextRenderComponent(font);
	FPSScript* pFPSScript = new FPSScript();
	pTextRender->SetColor({ 255,255,0 });
	go->AddComponent(pFPSComponent);
	go->AddComponent(pTextRender);
	go->AddComponent(pFPSScript);
	go->SetPosition(10, 10);
	scene.Add(go);

}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();
	{
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

			//Normal Update?

			while (lag >= secondsPerUpdate)
			{
				//FixedUpdate?
				sceneManager.Update(deltaTime);
				lag -= secondsPerUpdate;			 
			}
			renderer.Render();
		}
	}

	Cleanup();
}
