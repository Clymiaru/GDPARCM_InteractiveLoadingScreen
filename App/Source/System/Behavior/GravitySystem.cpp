#include "pch.h"
#include "GravitySystem.h"

GravitySystem::GravitySystem()
{
}

GravitySystem::~GravitySystem()
{
}

void GravitySystem::Update(float deltaTime)
{
	for (auto* component : m_GravityComponentList)
	{
		auto& transform    = component->GetTransform();
		const auto gravity = component->GetGravitationForce();
		transform.Move(sf::Vector2f{0.0f, gravity});
	}
}
