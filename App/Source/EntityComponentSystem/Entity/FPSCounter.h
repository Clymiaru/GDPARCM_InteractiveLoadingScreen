#pragma once
#include "AGameObject.h"

class FPSCounter final : public AGameObject
{
public:
	explicit FPSCounter();

	~FPSCounter() override;

	void Initialize() override;

	void ProcessInput(sf::Event event) override;

	void Update(float deltaTime) override;

	void Draw(sf::RenderWindow* targetWindow) override;

private:
	float m_UpdateTime;
	sf::Text* m_StatsText;
	int m_FramesPassed;

	void UpdateFPS(float elapsedTime);
};
