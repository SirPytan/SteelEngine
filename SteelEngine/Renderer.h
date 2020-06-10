#pragma once
#include "Singleton.h"
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, int x, int y, int width, int height) const;
		void RenderTexture(const Texture2D& texture, const SDL_Rect& sourceRect, const SDL_Rect& destinationRect) const;

		SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }
	private:
		SDL_Renderer* m_pRenderer{};
	};
}

