#pragma once
#include "ECS/ARenderSystem.h"
#include "ECS/Component/FPSCounterComponent.h"
#include "ECS/Component/TextComponent.h"

class TextRenderSystem : public ARenderSystem
{
public:
	TextRenderSystem();
	~TextRenderSystem() override;

	MAKE_SYSTEM(TextRenderSystem,
             Render,
          TextComponent,
       m_TextComponentList)

    void Render(sf::RenderWindow& window) override;

private:
	List<TextComponent*> m_TextComponentList;
	
};
