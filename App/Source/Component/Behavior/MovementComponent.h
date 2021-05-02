#pragma once
#include "Component/Data/TransformComponent.h"
#include "Component/Data/VelocityComponent.h"

#include "Core/EntitySystem/AComponent.h"

class MovementComponent : public AComponent
{
public:
	MovementComponent(Entity& owner,
					  TransformComponent& transform,
					  VelocityComponent& velocity);
	
	AComponent* Clone(Entity& newOwner) override;
	MAKE_COMPONENT(MovementComponent)

	TransformComponent& GetTransform() const;
	VelocityComponent& GetVelocity() const;
private:
	TransformComponent& m_Transform;
	VelocityComponent& m_Velocity;
	
};
