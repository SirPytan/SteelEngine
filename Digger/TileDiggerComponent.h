#pragma once
#include <BaseComponent.h>
#include "SpriteComponent.h"
#include "Subject.h"

class TileDiggerComponent : public dae::BaseComponent
{
public:
	TileDiggerComponent(const std::vector<std::weak_ptr<dae::GameObject>>& pTiles);
	~TileDiggerComponent();

	TileDiggerComponent(const TileDiggerComponent& other) = delete;
	TileDiggerComponent(TileDiggerComponent&& other) noexcept = delete;
	TileDiggerComponent& operator=(const TileDiggerComponent& other) = delete;
	TileDiggerComponent& operator=(TileDiggerComponent&& other) noexcept = delete;

	void AddObserver(Observer* observer);
	void RemoveObserver(Observer* observer);

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
private:
	SpriteComponent* m_pSprite = nullptr;
	std::vector<std::weak_ptr<dae::GameObject>> m_pTiles{};
	float m_MinDistance = 15.f;
	Subject* m_pSubject = nullptr;

};

