#include "SteelEnginePCH.h"
#include "BoxCollider2D.h"

BoxCollider2D::BoxCollider2D(SDL_Rect rect, bool isStatic)
	: m_Rect{rect}
	, m_IsStatic{isStatic}
{
}

void BoxCollider2D::Initialize()
{
}

void BoxCollider2D::Update(float deltaTime)
{
}

void BoxCollider2D::Render()
{
}
