#pragma once
#ifndef SCENE_MANAGER
#define SCENE_MANAGER
#include "Singleton.h"
#include <vector>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* CreateScene(const std::string& name);
		void SetActivScene(int index);
		void SetActivScene(const std::string& sceneName);
		void SetActivScene(Scene* pScene);
		Scene* GetSceneByName(const std::string& sceneName) const;
		Scene* GetActivScene() const { return m_pActivScene; }

		void Initialize();
		void Update(float deltaTime);
		void Render();
		void Cleanup();
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		Scene* m_pActivScene = nullptr;
		std::vector<Scene*> m_pScenes{};
	};
}
#endif
