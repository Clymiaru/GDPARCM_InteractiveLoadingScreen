#include "pch.h"
#include "BaseRunner.h"

#include "EntitySystem/EntityManager.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"
#include "EventSystem/EventBroadcaster.h"
#include "SceneManagement/SceneManager.h"
#include "SystemManagement/EntitySystemManager.h"

Resolution BaseRunner::WindowSize;

BaseRunner::BaseRunner(Resolution windowSize,
					   StringRef title,
					   const List<AScene*> availableScenes,
					   StringRef startingSceneName) :
	m_Event{}
{
	WindowSize        = std::move(windowSize);
	const auto width  = WindowSize.Width;
	const auto height = WindowSize.Height;
	m_Window.create(sf::VideoMode(width, height),
                    title,
                    sf::Style::Close);

	m_IsRunning = m_Window.isOpen();

	SceneManager::GetInstance().RegisterScenes(availableScenes);
	SceneManager::GetInstance().SetDefaultSceneNames({startingSceneName});
}

BaseRunner::~BaseRunner()
{
}

void BaseRunner::Run()
{
	SceneManager::GetInstance().LoadDefaultScenes();
	sf::Clock clock;
	
	while (m_IsRunning)
	{
		const auto dt = clock.restart();
		Initialize();
			// If there is a need to order an initialization,
			// redesign or add a second initialization block
		
		ProcessEvents();
			// Store all events polled
			// Dispatch the system-related events first -> execute
			// Dispatch the remaining polled events to the UI system first -> execute
			// Dispatch the remaining polled events to the ECS -> execute
			// Empty polled event list
		
		Update(dt.asSeconds());
			// Update ECS first
			// Update UI
			// Update System (if necessary)
		
		Render();
			// TODO (Maybe): Sprite batching rendering feature
			// Render ECS
			// Render UI
		
		Deinitialize();
			// Deinitialize all things that need to be deinitialized at this moment
			// Actual destruction of Entities or Widgets right after deinitialization	
	}
}

void BaseRunner::Initialize()
{
	SceneManager::GetInstance().InitializeScenes();
}

void BaseRunner::ProcessEvents()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_EventQueue.push(new WindowCloseEvent());
				m_IsRunning = false;
				break;
			case sf::Event::Resized:
				m_EventQueue.push(new WindowResizeEvent(event.size));
				break;
			case sf::Event::LostFocus:
				m_EventQueue.push(new WindowLostFocusEvent());
				break;
			case sf::Event::GainedFocus:
				m_EventQueue.push(new WindowFocusEvent());
				break;
			case sf::Event::KeyPressed:
				m_EventQueue.push(new KeyPressedEvent(event.key.code));
				break;
			case sf::Event::KeyReleased:
				m_EventQueue.push(new KeyReleasedEvent(event.key.code));
				break;
			case sf::Event::MouseWheelScrolled:
				m_EventQueue.push(new MouseScrolledEvent(event.mouseWheelScroll));
				break;
			case sf::Event::MouseButtonPressed:
				m_EventQueue.push(new MouseButtonPressedEvent(event.mouseButton));
				break;
			case sf::Event::MouseButtonReleased:
				m_EventQueue.push(new MouseButtonReleasedEvent(event.mouseButton));
				break;
			case sf::Event::MouseMoved:
				m_EventQueue.push(new MouseMoveEvent(event.mouseMove));
				break;
			default:
				break;
		}
	}

	while (!m_EventQueue.empty())
	{
		EntitySystemManager::GetInstance().ProcessEvents(*m_EventQueue.front());
		m_EventQueue.pop();
	}
}

void BaseRunner::Update(const float deltaTime)
{
	EntitySystemManager::GetInstance().Update(deltaTime);
}

void BaseRunner::Render()
{
	m_Window.clear();
	EntitySystemManager::GetInstance().Render(m_Window);
	m_Window.display();
}

void BaseRunner::Deinitialize()
{
	SceneManager::GetInstance().DeinitializeScenes();
	EntityManager::GetInstance().DestroyMarkedEntities();

	if (m_IsRunning == false)
	{
		m_Window.close();
	}
}
