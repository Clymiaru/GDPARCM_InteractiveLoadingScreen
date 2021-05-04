#include "pch.h"
#include "TextRenderSystem.h"

TextRenderSystem::TextRenderSystem()
{
}

TextRenderSystem::~TextRenderSystem()
{
}

void TextRenderSystem::Render(sf::RenderWindow& window)
{
	for (auto* component : m_TextComponentList)
	{
		auto& text = component->GetText();
		auto& transform = component->GetTransform().GetRawTransform();
		
		window.draw(text, transform);
	}
}
