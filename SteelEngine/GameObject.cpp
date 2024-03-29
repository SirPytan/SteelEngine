#include "SteelEnginePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Helpers.h"

dae::GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		SafeDelete(pComp);
	}
};

void dae::GameObject::Initialize()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Initialize();
	}
}

void dae::GameObject::Update(float deltaTime)
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Render();
	}

	if (m_pTexture)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}

}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

Elite::FVector3 dae::GameObject::GetPosition()
{
	return m_Transform.GetElitePosition();
}

Elite::FVector2 dae::GameObject::GetPosition2D()
{
	return m_Transform.GetElitePosition2D();
}

void dae::GameObject::AddComponent(BaseComponent* pComp)
{
	for (BaseComponent* component : m_pComponents)
	{
		if (component == pComp)
		{
			std::cout << "AddComponent: GameObject already contains this component!\n";
			return;
		}
	}

	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = this;

}

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
{
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);

	if (it == m_pComponents.end())
	{
		std::cout << "RemoveComponent: Component is not attached to this GameObject!\n";
		return;
	}

	m_pComponents.erase(it);
	pComp->m_pGameObject = nullptr;
}
