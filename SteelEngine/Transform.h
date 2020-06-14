#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "EMath.h"

namespace dae
{
	//struct Vector2
	//{
	//	float x = 0;
	//	float y = 0;
	//};

	class Transform final
	{
	public:
		const glm::vec3& GetPosition() const { return m_Position; }
		Elite::FVector3 GetElitePosition() const { return Elite::FVector3(m_Position.x, m_Position.y, m_Position.z); }
		Elite::FVector2 GetElitePosition2D() const { return Elite::FVector2(m_Position.x, m_Position.y); }
		void SetPosition(float x, float y, float z);
	private:
		glm::vec3 m_Position;
	};
}
