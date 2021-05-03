#include "pch.h"
#include "GravityComponent.h"

#include "ECS/Entity.h"

GravityComponent::GravityComponent(Entity& owner,
                                   TransformComponent& transform,
                                   float gravitationForce) :
	AComponent{owner},
	m_Transform{transform},
	m_GravitationForce{gravitationForce}
{
}

GravityComponent::~GravityComponent()
{
}

AComponent* GravityComponent::Clone(Entity& newOwner) 
{
	auto* transform = newOwner.GetComponent<TransformComponent>();

	ASSERT(transform != nullptr,
			GravityComponent,
			"Attempting to clone a component where the newOwner has no TransformComponent!")
	
	return new GravityComponent(newOwner,
								*transform,
								m_GravitationForce);
}

TransformComponent& GravityComponent::GetTransform() const
{
	return m_Transform;
}

float GravityComponent::GetGravitationForce() const
{
	return m_GravitationForce;
}

void GravityComponent::SetGravitationForce(float gravitationForce)
{
	m_GravitationForce = gravitationForce;
}
