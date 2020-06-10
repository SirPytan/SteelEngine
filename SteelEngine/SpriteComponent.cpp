#include "SteelEnginePCH.h"
#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(Texture2D* pTexture, const float spriteSheetLeft, const float spriteSheetTop, const float spriteSheetWidth, const float spriteSheetHeight, const int cols, const int rows, int framesPerSec, float scale)
	: m_pTexture{pTexture}
	, m_SpriteSheetLeft{ spriteSheetLeft }
	, m_SpriteSheetTop{ spriteSheetTop }
	, m_SpriteSheetWidth{ spriteSheetWidth }
	, m_SpriteSheetHeight{ spriteSheetHeight }
	, m_Cols{ cols }
	, m_Rows{ rows }
	, m_FramesPerSec{ framesPerSec }
	, m_Scale{ scale }
	, m_CurrentFrame{ 0 }
{
	if (m_pTexture == nullptr)
	{
		std::cout << "Sprite Texture is nullpointer";
	}
	m_FrameTime = 1.0f / m_FramesPerSec;
}

void SpriteComponent::InitDestinationRect()
{
	//TopLeftCorner
	m_DestinationRect.w = (m_SpriteSheetWidth / m_Cols) * m_Scale;
	m_DestinationRect.h = (m_SpriteSheetHeight / m_Rows) * m_Scale;
	m_DestinationRect.x = GetGameObject()->GetPosition().x; 
	m_DestinationRect.y = GetGameObject()->GetPosition().y;
}

void SpriteComponent::InitSourceRect()
{
	m_SourceRect.w = m_SpriteSheetWidth / m_Cols;
	m_SourceRect.h = m_SpriteSheetHeight / m_Rows;
	m_SourceRect.y = m_SpriteSheetTop;
	UpdateSourceRect();
}

void SpriteComponent::UpdateSourceRect()
{
	m_SourceRect.x = m_SpriteSheetLeft + m_CurrentFrame % m_Cols * m_SourceRect.w;
}


void SpriteComponent::Initialize()
{
}

void SpriteComponent::Update(float deltaTime)
{
}

void SpriteComponent::Render()
{
}
