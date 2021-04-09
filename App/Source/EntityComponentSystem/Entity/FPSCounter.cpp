#include "pch.h"
#include "FPSCounter.h"
#include <iostream>
#include "Core/BaseRunner.h"

FPSCounter::FPSCounter():
	AGameObject("FPSCounter"),
	m_UpdateTime{0},
	m_StatsText{nullptr},
	m_FramesPassed{0}
{
}

FPSCounter::~FPSCounter()
{
	delete m_StatsText->getFont();
	delete m_StatsText;
	AGameObject::~AGameObject();
}

void FPSCounter::Initialize()
{
	sf::Font* font = new sf::Font();
	font->loadFromFile("Media/Sansation.ttf");

	m_StatsText = new sf::Text();
	m_StatsText->setFont(*font);
	m_StatsText->setPosition(BaseRunner::WindowSize.Width - 150, BaseRunner::WindowSize.Height - 70);
	m_StatsText->setOutlineColor(sf::Color(255, 255, 255));
	m_StatsText->setOutlineThickness(2.5f);
	m_StatsText->setCharacterSize(35);
}

void FPSCounter::ProcessInput(sf::Event event)
{
}

void FPSCounter::Update(float deltaTime)
{
	UpdateFPS(deltaTime);
}

void FPSCounter::Draw(sf::RenderWindow* targetWindow)
{
	AGameObject::Draw(targetWindow);

	if (m_StatsText != nullptr)
		targetWindow->draw(*m_StatsText);
}

void FPSCounter::UpdateFPS(float elapsedTime)
{
	m_UpdateTime += elapsedTime;

	if (m_UpdateTime >= 1000.0f)
	{
		const auto fpsText = "FPS: " + std::to_string(m_FramesPassed) + "\n";
		m_StatsText->setString(fpsText.c_str());
		m_FramesPassed = 0;
		m_UpdateTime   = 0;
	}

	m_FramesPassed++;
}
