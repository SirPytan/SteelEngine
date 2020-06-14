#pragma once
#include "EMath.h"
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include <string>
#include <memory>
#include <vector>

namespace dae
{
	class BaseComponent;
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		Elite::FVector3 GetPosition();
		Elite::FVector2 GetPosition2D();

		void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (BaseComponent* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}

	private:
		Transform m_Transform{};
		std::shared_ptr<Texture2D> m_pTexture{};

		std::vector<BaseComponent*> m_pComponents;
	};
}
