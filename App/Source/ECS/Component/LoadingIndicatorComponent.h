#pragma once
#include "AComponent.h"
#include "TextComponent.h"

class LoadingIndicatorComponent : public AComponent
{
public:
	LoadingIndicatorComponent(Entity& owner,
							  TextComponent& textComponent,
							  int maxExpectedLoadedAssets);
	
	MAKE_COMPONENT(LoadingIndicatorComponent)

	void UpdateProgress(int currentProgress);
	void UpdateMaxProgress(int maxProgress);
	int GetCurrentProgress() const;
	int GetMaxExpectedProgress() const;

	TextComponent& GetTextComponent() const;
private:
	TextComponent& m_TextComponent;
	int m_CurrentProgress;
	int m_MaxExpectedLoadedAssets;
};
