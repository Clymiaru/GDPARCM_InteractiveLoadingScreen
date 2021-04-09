#pragma once
#include "AGameObject.h"

class IconObject final : public AGameObject
{
public:
	IconObject(const String& name,
	           int textureIndex);

	void Initialize() override;

	void ProcessInput(sf::Event event) override;

	void Update(float deltaTime) override;

private:
	int m_TextureIndex;
};
