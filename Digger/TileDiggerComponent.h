#pragma once
#include <BaseComponent.h>
#include "SpriteComponent.h"

class TileDiggerComponent : public dae::BaseComponent
{
public:
	TileDiggerComponent(const std::vector<std::weak_ptr<GameObject>>& pTiles);
	~TileDiggerComponent() = default;

	TileDiggerComponent(const TileDiggerComponent& other) = delete;
	TileDiggerComponent(TileDiggerComponent&& other) noexcept = delete;
	TileDiggerComponent& operator=(const TileDiggerComponent& other) = delete;
	TileDiggerComponent& operator=(TileDiggerComponent&& other) noexcept = delete;


protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
private:
	SpriteComponent* m_pSprite = nullptr;
	std::vector<std::weak_ptr<GameObject>> m_pTiles{};
	float m_MinDistance = 15.f;
};

