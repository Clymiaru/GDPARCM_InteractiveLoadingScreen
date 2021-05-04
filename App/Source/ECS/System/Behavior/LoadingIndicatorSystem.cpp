#include "pch.h"
#include "LoadingIndicatorSystem.h"

#include "AssetManagement/AssetManager.h"

LoadingIndicatorSystem::LoadingIndicatorSystem()
{
}

LoadingIndicatorSystem::~LoadingIndicatorSystem()
{
}

void LoadingIndicatorSystem::Update(float deltaTime)
{
	for (auto* component : m_LoadingIndicatorComponentList)
	{
		component->UpdateProgress(AssetManager::GetInstance().GetCurrentLoadedAsyncAssets());
		component->UpdateMaxProgress(AssetManager::GetInstance().GetMaxAsyncAssets());
		const auto progress    = component->GetCurrentProgress();
		const auto maxProgress = component->GetMaxExpectedProgress();

		if (maxProgress == 0)
		{
			component->GetTextComponent().UpdateText(std::to_string(0.0f));
		}
		else
		{
			component->GetTextComponent().UpdateText(std::to_string((float)progress / maxProgress));
		}
		
	}
}
