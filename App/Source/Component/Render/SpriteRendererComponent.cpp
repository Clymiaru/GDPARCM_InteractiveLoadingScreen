﻿#include "pch.h"
#include "SpriteRendererComponent.h" 


#include "Core/EntitySystem/Entity.h"

SpriteRendererComponent::SpriteRendererComponent(Entity& owner,
												 Texture& texture,
												 TransformComponent& transformComponent) :
	AComponent{owner},
	m_Sprite{texture.GetData()},
	m_Transform{transformComponent},
	m_Texture{texture}
{
	const auto textureSize = m_Sprite.getTexture()->getSize();
	m_Sprite.setOrigin(textureSize.x / 2.0f, textureSize.y / 2.0f);
}

SpriteRendererComponent::~SpriteRendererComponent()
{
}

AComponent* SpriteRendererComponent::Clone(Entity& newOwner)
{
	auto* transform = newOwner.GetComponent<TransformComponent>();
	
	ASSERT(transform != nullptr,
        MovementComponent,
        newOwner.GetName() << " entity has no TransformComponent bounded!")

    return new SpriteRendererComponent(newOwner,
    								   m_Texture,
    								   *newOwner.GetComponent<TransformComponent>());
}

const sf::Sprite& SpriteRendererComponent::GetSprite() const
{
	return m_Sprite;
}

const sf::Transform& SpriteRendererComponent::GetTransform() const
{
	return m_Transform.GetRawTransform();
}