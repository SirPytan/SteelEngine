#include "SteelEnginePCH.h"
#include "Texture2D.h"
#include <SDL.h>

dae::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

SDL_Texture* dae::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}

dae::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_pTexture = texture;
	int w, h;
	if (SDL_QueryTexture(texture, NULL, NULL, &w, &h) == 0)
	{
		m_Width = w;
		m_Height = h;
	}
	else
		std::cout << "Texture not valid\n";
}
