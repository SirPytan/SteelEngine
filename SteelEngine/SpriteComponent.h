#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <SDL.h>

using namespace dae;

enum class AnimationType : int
{
	OneFrame = 0,
	FromLeftToRight = 1,
	//FromRightToLeft = 2,
	FromTopToBottom = 3,
	//FromBottomToTop = 4,
	UseCompleteSpritesheet = 5
};

class SpriteComponent : public dae::BaseComponent
{
public:
	SpriteComponent(const std::string& texturePath, const int numberOfColumns, const int numberOfRows, int framesPerSec, float scale);
	SpriteComponent(std::shared_ptr<Texture2D> texture2D, const int numberOfColumns, const int numberOfRows, int framesPerSec, float scale);
	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) noexcept = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;
	//~SpriteComponent() override;

	//Row and Column start with 1,2,3,...
	void SetAnimationParameters(AnimationType type, unsigned int column, unsigned int row, bool isStatic);
	void SetDestinationRectPosition(int x, int y);
	unsigned int GetRow() { return m_Row; }
	unsigned int GetColumn() { return m_Column; }

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	//Sprite Properties
	std::shared_ptr<Texture2D> m_pTexture{};
	float m_FrameTime{};
	const int m_SpriteSheetWidth;
	const int m_SpriteSheetHeight;
	const int m_Cols;
	const int m_Rows;
	int m_FramesPerSec{};
	float m_Scale{};
	AnimationType m_AnimationType = AnimationType::OneFrame;
	unsigned int m_Row{};
	unsigned int m_Column{};
	bool m_IsStatic = false;

	//Sprite related datamembers
	int m_CurrentFrame;
	SDL_Rect m_SourceRect{};
	SDL_Rect m_DestinationRect{};

	//Update values
	float m_AccumulatedTime{};
	int m_CurrentRow{};
	int m_CurrentColumn{};

	//Functions
	void InitDestinationRect();
	void InitSourceRect();
};

