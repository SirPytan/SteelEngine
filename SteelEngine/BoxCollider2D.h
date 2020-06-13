#pragma once
#include "BaseComponent.h"
#include <SDL.h>

using namespace dae;

class BoxCollider2D : public dae::BaseComponent
{
public:
	BoxCollider2D(SDL_Rect rect, bool isStatic = true);
	BoxCollider2D(const BoxCollider2D& other) = delete;
	BoxCollider2D(BoxCollider2D&& other) noexcept = delete;
	BoxCollider2D& operator=(const BoxCollider2D& other) = delete;
	BoxCollider2D& operator=(BoxCollider2D&& other) noexcept = delete;
	//~BoxCollider2D() override;

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;
private:
	SDL_Rect m_Rect{};
	bool m_IsStatic = true;
	const float m_Gravity = 9.81f
};

