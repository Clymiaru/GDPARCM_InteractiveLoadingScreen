#include "pch.h"
#include "DestroyOnClickSystem.h"
#include "Event/MouseEvent.h"
#include "ECS/EntityManager.h"

DestroyOnClickSystem::DestroyOnClickSystem()
{
}

DestroyOnClickSystem::~DestroyOnClickSystem()
{
}

void DestroyOnClickSystem::ProcessEvent(Event& event)
{
	for (auto* component : m_DestroyOnClickComponentList)
	{
		const auto position = component->GetTransform().GetPosition();
		if (event.GetEventType() == EventType::MouseButtonPressed)
		{
			auto& mouseEvent  = static_cast<MouseButtonPressedEvent&>(event);
			const auto mouseX = mouseEvent.GetX();
			const auto mouseY = mouseEvent.GetY();
			
			if (position.x - 50.0f < mouseX &&
				position.x + 50.0f > mouseX &&
				position.y - 50.0f < mouseY &&
				position.y + 50.0f > mouseY)
			{
				INFO_LOG(DestroyOnClickSystem,
						"Destroy entity " << component->GetName() << ".")
				EntityManager::GetInstance().DestroyEntity(component->GetOwner());
			}
		}
	}
}
