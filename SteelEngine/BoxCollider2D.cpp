#include "SteelEnginePCH.h"
#include "BoxCollider2D.h"
#include "Utils.h"

BoxCollider2D::BoxCollider2D(std::vector<std::weak_ptr<GameObject>> dynamicGameObjects, SDL_Rect rect, bool isStatic)
	: m_DynamicGameObjects{ dynamicGameObjects }
	, m_Rect{ rect }
	, m_IsStatic{ isStatic }
{
	m_Center = Elite::FVector2(rect.x + (rect.w * 0.5f), (rect.y - (rect.h * 0.5f)));
}

BoxCollider2D::~BoxCollider2D()
{
}

std::vector<dae1::Point2f> BoxCollider2D::GetDAERectCornerPoints() const
{
	std::vector<dae1::Point2f> points;
	points.push_back(dae1::Point2f((float)m_Rect.x, (float)m_Rect.y));
	points.push_back(dae1::Point2f((float)(m_Rect.x + m_Rect.w), (float)m_Rect.y));
	points.push_back(dae1::Point2f((float)(m_Rect.x + m_Rect.w), (float)(m_Rect.y + m_Rect.h)));
	points.push_back(dae1::Point2f((float)m_Rect.x, (float)(m_Rect.y + m_Rect.h)));

	return points;
}

void BoxCollider2D::Initialize()
{

}

void BoxCollider2D::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	for (std::weak_ptr<GameObject> wGameObject : m_DynamicGameObjects)
	{
		if (!wGameObject.expired())
		{
			auto sGameObject = wGameObject.lock();
			if (sGameObject)
			{
				auto pos = sGameObject->GetPosition2D();
				Elite::FPoint2 point1 = Elite::FPoint2(pos);
				Elite::FPoint2 point2 = Elite::FPoint2(GetGameObject()->GetPosition2D());
				if (Elite::SqrDistance(point1, point2) < Elite::Square(m_MinDistance))
				{
					Utils::SetColor(dae1::Color4f(1, 1, 1, 1));//White
					Utils::DrawArc(dae1::Point2f(point2.x, point2.y), m_MinDistance, m_MinDistance, 0.f, 360.f, 1.f);
					BoxCollider2D* pBox = sGameObject->GetComponent<BoxCollider2D>();
					if (pBox != nullptr)
					{
						dae1::Rectf dynamicRectf = pBox->GetDAERect();
						Utils::SetColor(dae1::Color4f(1, 0, 0, 1));//Red
						Utils::DrawRect(dynamicRectf);
						Utils::SetColor(dae1::Color4f(0, 1, 0, 1));//Green
						Utils::DrawRect(GetDAERect());
						if (Utils::IsOverlapping(dynamicRectf, GetDAERect()))
						{
							//HorizontalRay
							dae1::Point2f leftMiddle = dae1::Point2f(dynamicRectf.left, dynamicRectf.bottom + (dynamicRectf.height * 0.5f));
							dae1::Point2f rightMiddle = dae1::Point2f(dynamicRectf.left + dynamicRectf.width, dynamicRectf.bottom + (dynamicRectf.height * 0.5f));
							Utils::HitInfo hitInfo{};
							Utils::Raycast(GetDAERectCornerPoints(), leftMiddle, rightMiddle, hitInfo);

							//VerticalRay
						}

					}
				}
			}

		}
	}
}

void BoxCollider2D::Render()
{

}
