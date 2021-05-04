#include "pch.h"
#include "ButtonEventSystem.h"

#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

ButtonEventSystem::ButtonEventSystem()
{
}

ButtonEventSystem::~ButtonEventSystem()
{
}

void ButtonEventSystem::ProcessEvent(Event& event)
{
	for (auto* component : m_ButtonComponentList)
	{
		auto& buttonRect = component->GetButtonRect();
		
		if (event.GetEventType() == EventType::MouseButtonPressed)
		{
			auto& mouseButtonPressed = static_cast<MouseButtonPressedEvent&>(event);
			auto mousePosition = sf::Vector2f(mouseButtonPressed.GetX(), mouseButtonPressed.GetY());
			
			if (buttonRect.contains(mousePosition))
			{
				component->Execute();
			}
		}
		
	}
}
