#include "pch.h"
#include "BaseRunner.h"

#include "EntityComponentSystem/Entity/BGObject.h"
#include "EntityComponentSystem/Entity/FPSCounter.h"
#include "EntityComponentSystem/GameObjectManager.h"
#include "EntityComponentSystem/Entity/TextureDisplay.h"
#include "AssetSystem/TextureManager.h"

Resolution BaseRunner::WindowSize;

BaseRunner::BaseRunner(Resolution windowSize,
					   StringRef title) :
	m_Event{}
{
	WindowSize = std::move(windowSize);

	m_Window.create(sf::VideoMode(WindowSize.Width, WindowSize.Height),
					title,
					sf::Style::Close);

	// //load initial textures
	// TextureManager::GetInstance()->LoadFromAssetList();
	//
	// m_Window.setFramerateLimit(60);
	// m_Window.setVerticalSyncEnabled(false);
	//
	// //load objects
	// auto* bgObject = new BGObject("BGObject");
	// GameObjectManager::GetInstance()->AddObject(bgObject);
	//
	// auto* display = new TextureDisplay();
	// GameObjectManager::GetInstance()->AddObject(display);
	//
	// auto* fpsCounter = new FPSCounter();
	// GameObjectManager::GetInstance()->AddObject(fpsCounter);
}

void BaseRunner::Run()
{
	sf::Clock clock;
	
	while (m_Window.isOpen())
	{
		const auto dt = clock.restart();
		ProcessEvents();
		Update(dt.asSeconds());
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
			default:
				//GameObjectManager::GetInstance()->ProcessInput(event);
				break;
		}
	}
}

void BaseRunner::Update(float deltaTime)
{
	GameObjectManager::GetInstance()->Update(deltaTime);
}

void BaseRunner::Render()
{
	m_Window.clear();
	GameObjectManager::GetInstance()->Draw(&m_Window);
	m_Window.display();
}
