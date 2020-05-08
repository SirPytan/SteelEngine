#pragma once
#include "GameObject.h"

namespace dae
{
	class GameObject;

	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		BaseComponent();
		virtual ~BaseComponent() = default;

		GameObject* GetGameObject() const { return m_pGameObject; }

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Render() = 0;

	protected:
		GameObject* m_pGameObject;

	};

}


