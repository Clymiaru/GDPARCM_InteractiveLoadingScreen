#include "pch.h"
#include "MovementComponent.h"

#include "Core/EntitySystem/Entity.h"

MovementComponent::MovementComponent(Entity& owner,
                                     TransformComponent& transform,
                                     VelocityComponent& velocity) :
	AComponent{owner},
	m_Transform{transform},
	m_Velocity{velocity}
{
}

AComponent* MovementComponent::Clone(Entity& newOwner)
{
	auto* transform = newOwner.GetComponent<TransformComponent>();
	auto* velocity = newOwner.GetComponent<VelocityComponent>();
	
	ASSERT(transform != nullptr,
            GravityComponent,
            "Attempting to clone a component where the newOwner has no TransformComponent!")

	ASSERT(velocity != nullptr,
            GravityComponent,
            "Attempting to clone a component where the newOwner has no VelocityComponent!")
	
    return new MovementComponent(newOwner,
                                *transform,
                                *velocity);
}

TransformComponent& MovementComponent::GetTransform() const
{
	return m_Transform;
}

VelocityComponent& MovementComponent::GetVelocity() const
{
	return m_Velocity;
}
