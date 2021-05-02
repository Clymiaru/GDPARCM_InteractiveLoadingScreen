#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "Component/Render/SpriteRendererComponent.h"
#include "Core/SystemManagement/ASystem.h"
#include "Core/SystemManagement/ARenderSystem.h"

class SpriteRendererSystem final : public ARenderSystem
{
public:
	SpriteRendererSystem();
	~SpriteRendererSystem() override;

	MAKE_SYSTEM(SpriteRendererSystem,
             Render,
          SpriteRendererComponent,
       m_SpriteRendererComponentList)

	void Render(sf::RenderWindow& window) override;

private:
	List<SpriteRendererComponent*> m_SpriteRendererComponentList;
};
