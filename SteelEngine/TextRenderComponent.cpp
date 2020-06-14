#include "SteelEnginePCH.h"
#include "TextRenderComponent.h"
#include "Renderer.h"

TextRenderComponent::TextRenderComponent(const std::shared_ptr<Font>& font, const std::string& text, const SDL_Color color)
	: m_Font{font}
	, m_Text{text}
	, m_Color{color}
	, m_NeedsUpdate{true}
	, m_Texture{nullptr}
{}

void TextRenderComponent::SetColor(SDL_Color color)
{
	m_Color = color;
}

void TextRenderComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextRenderComponent::SetTextSize(unsigned int size)
{
	m_Font->SetSize(size);
	m_NeedsUpdate = true;
}

void TextRenderComponent::Initialize()
{
}

void TextRenderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void TextRenderComponent::Render()
{
	if (m_Texture != nullptr)
	{
		Elite::FVector2 pos = m_pGameObject->GetPosition2D();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}
