#pragma once
#include "Component/Data/TransformComponent.h"

#include "Core/EntitySystem/AComponent.h"

class DestroyOnClickComponent final : public AComponent
{
public:
	explicit DestroyOnClickComponent(Entity& owner,
									 TransformComponent& transform);
	~DestroyOnClickComponent();

	AComponent* Clone(Entity& newOwner) override;
	MAKE_COMPONENT(DestroyOnClick);

	TransformComponent& GetTransform() const;
private:
	TransformComponent& m_Transform;
};
