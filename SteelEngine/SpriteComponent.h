#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <SDL.h>

using namespace dae;

class SpriteComponent : public dae::BaseComponent
{
	SpriteComponent(Texture2D* pTexture, const float spriteSheetLeft, const float spriteSheetTop, const float spriteSheetWidth, const float spriteSheetHeight, const int cols, const int rows, int framesPerSec, float scale);
	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) noexcept = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;
	//~SpriteComponent() override;

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	//Sprite Properties
	const Texture2D* m_pTexture = nullptr;
	float m_FrameTime{};
	float m_SpriteSheetTop{};
	const float m_SpriteSheetLeft{};
	const float m_SpriteSheetWidth{};
	const float m_SpriteSheetHeight{};
	const int m_Cols{};
	const int m_Rows{};
	int m_FramesPerSec{};
	float m_Scale{};

	//Sprite related datamembers
	int m_CurrentFrame;
	SDL_Rect m_SourceRect{};
	SDL_Rect m_DestinationRect{};

	//Functions
	void InitDestinationRect();
	void InitSourceRect();
	void UpdateSourceRect();
};

