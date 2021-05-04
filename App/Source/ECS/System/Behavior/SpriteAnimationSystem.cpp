#include "pch.h"
#include "SpriteAnimationSystem.h"

SpriteAnimationSystem::SpriteAnimationSystem()
{
}

SpriteAnimationSystem::~SpriteAnimationSystem()
{
}

void SpriteAnimationSystem::Update(const float deltaTime)
{
	for (auto* component : m_SpriteAnimatorComponentList)
	{
		component->UpdateTime(deltaTime);
		if (component->GetElapsedTime() > component->GetTimeBetweenFrames())
		{
			component->AdvanceFrame();
		}
		
		const auto frameWidth  = component->GetFrameWidth();
		const auto frameHeight = component->GetFrameHeight();
		const auto currentRow = component->GetCurrentRow();
		const auto currentCol = component->GetCurrentCol();

		auto textureRect = sf::IntRect(currentCol * frameWidth, currentRow * frameHeight,
											 frameWidth, frameHeight);
		
		component->GetSpriteRenderer().SetTextureRect(textureRect);
	}
}
