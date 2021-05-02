#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/String.hpp>

#include "Core/EntitySystem/AComponent.h"
#include "Component/Data/TransformComponent.h"

#include "Asset/Texture/Texture.h"

class SpriteRendererComponent final : public AComponent
{
public:
	
	explicit SpriteRendererComponent(Entity& owner,
	                                 Texture& texture,
	                                 TransformComponent& transformComponent);
	~SpriteRendererComponent() override;

	MAKE_COMPONENT(SpriteRenderer)

	AComponent* Clone(Entity& newOwner) override;

	const sf::Sprite& GetSprite() const;
	const sf::Transform& GetTransform() const;
private:
	sf::Sprite m_Sprite;
	Texture& m_Texture;
	TransformComponent& m_Transform;
};
