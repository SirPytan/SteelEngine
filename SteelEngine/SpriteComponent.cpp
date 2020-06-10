#include "SteelEnginePCH.h"
#include "SpriteComponent.h"
#include "Renderer.h"

SpriteComponent::SpriteComponent(Texture2D* pTexture, const int cols, const int rows, int framesPerSec, float scale)
	: m_pTexture{pTexture}
	, m_SpriteSheetWidth{ pTexture->GetWidth() }
	, m_SpriteSheetHeight{ pTexture->GetHeight() }
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

	InitDestinationRect();
	InitSourceRect();
}

void SpriteComponent::InitDestinationRect()
{
	//TopLeftCorner
	m_DestinationRect.w = (int)((m_SpriteSheetWidth / m_Cols) * m_Scale);
	m_DestinationRect.h = (int)((m_SpriteSheetHeight / m_Rows) * m_Scale);
	m_DestinationRect.x = (int)(GetGameObject()->GetPosition().x); 
	m_DestinationRect.y = (int)(GetGameObject()->GetPosition().y);
}

void SpriteComponent::InitSourceRect()
{
	m_SourceRect.w = m_SpriteSheetWidth / m_Cols;
	m_SourceRect.h = m_SpriteSheetHeight / m_Rows;
	m_SourceRect.y = 0;
	m_SourceRect.x = 0;
}


void SpriteComponent::SetAnimationParameters(AnimationType type, unsigned int column, unsigned int row)
{
	m_AnimationType = type;
	m_Column = column-1;
	m_Row = row-1;
	m_SourceRect.x = m_Column * m_SourceRect.w;
	m_SourceRect.y = m_Row * m_SourceRect.h;
}

void SpriteComponent::Initialize()
{
}

void SpriteComponent::Update(float deltaTime)
{

	m_DestinationRect.x = (int)(GetGameObject()->GetPosition().x);
	m_DestinationRect.y = (int)(GetGameObject()->GetPosition().y);

	m_AccumulatedTime += deltaTime;
	if (m_AccumulatedTime >= m_FrameTime)
	{
		//++m_CurrentFrame %= (m_Cols * m_Rows);

		switch (m_AnimationType)
		{
		case AnimationType::OneFrame:
			break;
		case AnimationType::FromLeftToRight:
			++m_CurrentFrame;
			m_CurrentFrame %= m_Cols;
			m_SourceRect.x = m_CurrentFrame * m_SourceRect.w;
			break;
		case AnimationType::FromTopToBottom:
			++m_CurrentFrame;
			m_CurrentFrame %= m_Rows;
			m_SourceRect.y = m_CurrentFrame * m_SourceRect.h;
			break;
		case AnimationType::UseCompleteSpritesheet:
			++m_CurrentFrame;
			if (m_CurrentFrame > m_Cols)
			{
				m_CurrentColumn = 0;
				m_CurrentRow++;
			}
			else
			{
				m_CurrentColumn++;
			}
			if (m_CurrentRow > m_Rows)
			{
				m_CurrentRow = 0;
				m_CurrentFrame = 0;
			}

			m_SourceRect.y = m_CurrentRow * m_SourceRect.h;
			m_SourceRect.x = m_CurrentColumn * m_SourceRect.w;
			break;
		default:
			break;
		}

		m_AccumulatedTime -= m_FrameTime;
	}


}

void SpriteComponent::Render()
{
	dae::Renderer::GetInstance().RenderTexture(*m_pTexture, m_SourceRect, m_DestinationRect);
}
