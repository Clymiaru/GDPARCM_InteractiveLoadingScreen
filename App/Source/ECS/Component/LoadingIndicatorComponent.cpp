﻿#include "pch.h"
#include "LoadingIndicatorComponent.h"

LoadingIndicatorComponent::LoadingIndicatorComponent(Entity& owner,
													TextComponent& textComponent,
													int maxExpectedLoadedAssets) :
	AComponent{owner},
	m_TextComponent{textComponent},
	m_CurrentProgress{0},
	m_MaxExpectedLoadedAssets{maxExpectedLoadedAssets}
{
}

void LoadingIndicatorComponent::UpdateProgress(int currentProgress)
{
	m_CurrentProgress = currentProgress;
}

int LoadingIndicatorComponent::GetCurrentProgress() const
{
	return m_CurrentProgress;
}

int LoadingIndicatorComponent::GetMaxExpectedProgress() const
{
	return m_MaxExpectedLoadedAssets;
}

TextComponent& LoadingIndicatorComponent::GetTextComponent() const
{
	return m_TextComponent;
}

