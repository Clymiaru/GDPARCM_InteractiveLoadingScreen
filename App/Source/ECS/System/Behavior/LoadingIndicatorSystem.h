#pragma once
#include "ECS/ABehaviorSystem.h"
#include "ECS/Component/LoadingIndicatorComponent.h"

class LoadingIndicatorSystem : public ABehaviorSystem
{
public:
	LoadingIndicatorSystem();
	~LoadingIndicatorSystem() override;
	
	MAKE_SYSTEM(LoadingIndicatorSystem,
         Behavior,
      LoadingIndicatorComponent,
   m_LoadingIndicatorComponentList)

    void Update(float deltaTime) override;

private:
	List<LoadingIndicatorComponent*> m_LoadingIndicatorComponentList;
};
