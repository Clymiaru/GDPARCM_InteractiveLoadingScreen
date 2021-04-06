#include "pch.h"
#include "BaseRunner.h"

Resolution BaseRunner::WindowSize;
Uint32 BaseRunner::FramerateLimit;

BaseRunner::BaseRunner(Resolution resolution,
					   StringRef appName,
					   Uint32 maxFramerate) :
	m_Event{}
{
	WindowSize = std::move(resolution);
	FramerateLimit = maxFramerate;
	
	m_Window.create(sf::VideoMode(WindowSize.Width, WindowSize.Height),
					appName,
					sf::Style::Close);

	m_Window.setFramerateLimit(FramerateLimit);
	m_Window.setVerticalSyncEnabled(false);
}

void BaseRunner::Run()
{
	while (m_Window.isOpen())
	{
		ProcessEvents();
		// Update();
		Render();
	}
}

void BaseRunner::ProcessEvents()
{
	while (m_Window.pollEvent(m_Event))
	{
		switch (m_Event.type)
		{
			case sf::Event::Closed:
				m_Window.close();
				break;
			case sf::Event::Resized:
				break;
			case sf::Event::LostFocus:
				break;
			case sf::Event::GainedFocus:
				break;
			case sf::Event::TextEntered:
				break;
			case sf::Event::KeyPressed:
				break;
			case sf::Event::KeyReleased:
				break;
			case sf::Event::MouseWheelMoved:
				break;
			case sf::Event::MouseWheelScrolled:
				break;
			case sf::Event::MouseButtonPressed:
				break;
			case sf::Event::MouseButtonReleased:
				break;
			case sf::Event::MouseMoved:
				break;
			case sf::Event::MouseEntered:
				break;
			case sf::Event::MouseLeft:
				break;
			case sf::Event::JoystickButtonPressed:
				break;
			case sf::Event::JoystickButtonReleased:
				break;
			case sf::Event::JoystickMoved:
				break;
			case sf::Event::JoystickConnected:
				break;
			case sf::Event::JoystickDisconnected:
				break;
			case sf::Event::TouchBegan:
				break;
			case sf::Event::TouchMoved:
				break;
			case sf::Event::TouchEnded:
				break;
			case sf::Event::SensorChanged:
				break;
			case sf::Event::Count:
				break;
			default: ;
		}
	}

	// Activate events
}

void BaseRunner::Update(float deltaTime)
{
}

void BaseRunner::Render()
{
	m_Window.clear();


	m_Window.display();
}
