#pragma once
#include "AGameObject.h"

class BGObject final : public AGameObject
{
public:
	explicit BGObject(const String& name);

	void Initialize() override;

	void ProcessInput(sf::Event event) override;

	void Update(float deltaTime) override;

private:
	const float SPEED_MULTIPLIER = 100.0f;
};
