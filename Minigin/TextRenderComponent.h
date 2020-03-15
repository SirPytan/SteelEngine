#pragma once
#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "Font.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Texture2D.h"

using namespace dae;

class TextRenderComponent : public BaseComponent
{
public:
	TextRenderComponent(const std::shared_ptr<Font>& font, const std::string& text = "-", const SDL_Color color = {255,255,255});

	TextRenderComponent(const TextRenderComponent& other) = delete;
	TextRenderComponent(TextRenderComponent&& other) noexcept = delete;
	TextRenderComponent& operator=(const TextRenderComponent& other) = delete;
	TextRenderComponent& operator=(TextRenderComponent&& other) noexcept = delete;
	virtual ~TextRenderComponent() = default;

	void SetColor(SDL_Color color);
	void SetText(const std::string& text);

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() override;

private:
	bool m_NeedsUpdate;
	std::shared_ptr<Font> m_Font;
	std::string m_Text;
	SDL_Color m_Color;
	Transform m_Transform;
	std::shared_ptr<Texture2D> m_Texture;
};

