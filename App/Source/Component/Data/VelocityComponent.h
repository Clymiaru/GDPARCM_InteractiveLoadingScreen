#pragma once
#include <SFML/System/Vector2.hpp>

#include "Core/EntitySystem/AComponent.h"

class VelocityComponent final : public AComponent
{
public:
	explicit VelocityComponent(Entity& owner,
	                           const sf::Vector2f& initialVelocity = sf::Vector2f(0.0f,0.0f));
	~VelocityComponent() override;

	AComponent* Clone(Entity& newOwner) override;

	MAKE_COMPONENT(Velocity)

	const sf::Vector2f& GetVelocity() const;
    void SetVelocity(const sf::Vector2f& velocity) const;

	void AddVelocity(const sf::Vector2f& addVector);
	void ScaleVelocity(float scaleAmount);
	void ScaleVelocity(const sf::Vector2f& scaleVector);
private:
	sf::Vector2f m_Velocity;
};