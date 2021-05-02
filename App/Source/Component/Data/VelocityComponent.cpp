#include "pch.h"
#include "VelocityComponent.h"

VelocityComponent::VelocityComponent(Entity& owner,
									 const sf::Vector2f& initialVelocity) :
	AComponent{owner},
	m_Velocity{initialVelocity}
{
}

VelocityComponent::~VelocityComponent()
{
}

AComponent* VelocityComponent::Clone(Entity& newOwner)
{
	return new VelocityComponent(newOwner, m_Velocity);
}

const sf::Vector2f& VelocityComponent::GetVelocity() const
{
	return m_Velocity;
}

void VelocityComponent::SetVelocity(const sf::Vector2f& velocity) const
{
}

void VelocityComponent::AddVelocity(const sf::Vector2f& addVector)
{
	m_Velocity += addVector;
}

void VelocityComponent::ScaleVelocity(float scaleAmount)
{
	m_Velocity *= scaleAmount;
}

void VelocityComponent::ScaleVelocity(const sf::Vector2f& scaleVector)
{
	m_Velocity.x *= scaleVector.x;
	m_Velocity.y *= scaleVector.y;
}
