#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

class BaseComponent;

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		Vector2 GetPosition();

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
		Transform m_Transform;
		std::shared_ptr<Texture2D> m_Texture{};

		std::vector<BaseComponent*> m_pComponents;
	};
}
