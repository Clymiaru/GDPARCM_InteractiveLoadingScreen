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
		auto progress = component->GetCurrentProgress();
		auto maxProgress = component->GetMaxExpectedProgress();
		
		component->GetTextComponent().UpdateText(std::to_string((float)progress / maxProgress));
	}
}
