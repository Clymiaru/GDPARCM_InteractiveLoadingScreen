#include "pch.h"
#include "DestroyOnClickComponent.h"

DestroyOnClickComponent::DestroyOnClickComponent(Entity& owner,
												 TransformComponent& transform) :
	AComponent{owner},
	m_Transform{transform}
{
}

DestroyOnClickComponent::~DestroyOnClickComponent()
{
}

AComponent* DestroyOnClickComponent::Clone(Entity& newOwner)
{
	return new DestroyOnClickComponent(newOwner, m_Transform);
}

TransformComponent& DestroyOnClickComponent::GetTransform() const
{
	return m_Transform;
}
