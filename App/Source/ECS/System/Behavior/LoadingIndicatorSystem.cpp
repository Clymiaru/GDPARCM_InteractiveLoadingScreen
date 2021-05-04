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

		auto text = std::stringstream();
		
		if (progress == maxProgress)
		{
			component->ExecuteOnComplete();
			text << "Complete!";
		}
		else
		{
			text << progress << " / " << maxProgress;
		}

		component->GetTextComponent().UpdateText(text.str());

		
	}
}
