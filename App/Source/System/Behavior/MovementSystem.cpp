#include "pch.h"
#include "MovementSystem.h"

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::Update(const float deltaTime)
{
	for (auto* component : m_MovementComponentList)
	{
		auto& transform = component->GetTransform();
		auto& velocity = component->GetVelocity();

		transform.Move(velocity.GetVelocity() * deltaTime);
	}
}
