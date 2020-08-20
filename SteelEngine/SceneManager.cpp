#include "SteelEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Scene.cpp"

dae::SceneManager::SceneManager()
	: m_pActivScene{nullptr}
{}

void dae::SceneManager::Initialize()
{
	for (auto& scene : m_pScenes)
	{
		scene->Initialize();
	}
}

void dae::SceneManager::FixedUpdate()
{
	m_pActivScene->FixedUpdate();
}

void dae::SceneManager::Update(float deltaTime)
{
	m_pActivScene->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_pActivScene->Render();
}

void dae::SceneManager::Cleanup()
{
	for (Scene* pScene : m_pScenes)
	{
		delete pScene;
		pScene = nullptr;
	}
	m_pActivScene = nullptr;
}

dae::Scene* dae::SceneManager::CreateScene(const std::string& name)
{
	auto scene = new Scene(name);
	m_pScenes.push_back(scene);
	return scene;
}

void dae::SceneManager::SetActivScene(int index)
{
	m_pActivScene = m_pScenes[index];
}

void dae::SceneManager::SetActivScene(const std::string& sceneName)
{
	Scene* pScene = GetSceneByName(sceneName);
	if (pScene != nullptr)
	{
		m_pActivScene = pScene;
	}
	else
		std::cout << "Scene with the name: " << sceneName << " does not exist, so it can't be set as activ scene.\n";
}

void dae::SceneManager::SetActivScene(Scene* pScene)
{
	m_pActivScene = pScene;
}

Scene* dae::SceneManager::GetSceneByName(const std::string& sceneName) const
{
	for (Scene* pScene : m_pScenes)
	{
		if (pScene->GetName() == sceneName)
		{
			return pScene;
		}
	}

	return nullptr;
}

