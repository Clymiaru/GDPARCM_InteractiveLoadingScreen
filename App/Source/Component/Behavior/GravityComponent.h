#pragma once
#include "Component/Data/TransformComponent.h"

class GravityComponent final: public AComponent
{
public:
	GravityComponent(Entity& owner,
					 TransformComponent& transform,
					 float gravitationForce);
	~GravityComponent();

	AComponent* Clone(Entity& newOwner) override;

	MAKE_COMPONENT(GravityComponent)

	TransformComponent& GetTransform() const;

	float GetGravitationForce() const;
	void SetGravitationForce(float gravitationForce);

private:
	TransformComponent& m_Transform;
	float m_GravitationForce;
};
