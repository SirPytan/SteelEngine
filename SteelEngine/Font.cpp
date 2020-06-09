#include "SteelEnginePCH.h"
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* dae::Font::GetFont() const
{
	return m_pFont;
}

dae::Font::Font(const std::string& fullPath, unsigned int size)
	: m_pFont{ nullptr }
	, m_FontPath{fullPath}
	, m_Size{ size }
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

dae::Font::~Font()
{
	TTF_CloseFont(m_pFont);
}

//Added by Daniel Patyk
void dae::Font::SetSize(unsigned int size)
{
	m_pFont = TTF_OpenFont(m_FontPath.c_str(), size);
	if (m_pFont == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font to set new size: ") + SDL_GetError());
	}
}

