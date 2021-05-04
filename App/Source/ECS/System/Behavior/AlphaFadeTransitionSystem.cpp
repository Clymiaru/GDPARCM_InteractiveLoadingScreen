#include "pch.h"
#include "AlphaFadeTransitionSystem.h"

AlphaFadeTransitionSystem::AlphaFadeTransitionSystem()
{
}

AlphaFadeTransitionSystem::~AlphaFadeTransitionSystem()
{
}

void AlphaFadeTransitionSystem::Update(float deltaTime)
{
	for (auto* component : m_AlphaFadeComponentList)
	{
		component->UpdateElapsedTime(deltaTime);
		const auto currentAlpha = component->GetCurrentAlpha();
		component->GetSprite().SetAlpha(currentAlpha);
	}
}
