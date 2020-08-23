#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include "SceneManager.h"
#include <memory>
#include "EMath.h"
#include <vector>
#include "Structs.h"

using namespace dae;

class BoxCollider2D : public dae::BaseComponent
{
public:
	BoxCollider2D(std::vector<std::weak_ptr<GameObject>>* pDynamicGameObjects, SDL_Rect rect, bool isStatic = true);
	BoxCollider2D(const BoxCollider2D& other) = delete;
	BoxCollider2D(BoxCollider2D&& other) noexcept = delete;
	BoxCollider2D& operator=(const BoxCollider2D& other) = delete;
	BoxCollider2D& operator=(BoxCollider2D&& other) noexcept = delete;
	~BoxCollider2D() override;

	void UpdatePosition(int x, int y) { m_Rect.x = x; m_Rect.y = y; }
	SDL_Rect GetSDLRect() const { return m_Rect; }
	dae1::Rectf GetDAERect() const { return dae1::Rectf((float)m_Rect.x, (float)(m_Rect.y + m_Rect.h), (float)m_Rect.w, (float)m_Rect.h); }
	std::vector<dae1::Point2f> GetDAERectCornerPoints() const;
	bool IsOverlapping() { return m_IsOverlapping; }
	std::vector<std::weak_ptr<GameObject>> GetOverlappingGameObjects() { return m_pWeakOverlappingGameObjects; }

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
private:
	SDL_Rect m_Rect{};
	bool m_IsOverlapping = false;
	bool m_IsStatic = true;
	const float m_Gravity = 9.81f;
	const float m_MinDistance = 25;
	Elite::FVector2 m_Center{};
	std::vector<std::weak_ptr<GameObject>>* m_pDynamicGameObjects;
	std::vector<std::weak_ptr<GameObject>> m_pWeakOverlappingGameObjects{};
};

