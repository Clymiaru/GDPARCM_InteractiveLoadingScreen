#pragma once
#include "ECS/ABehaviorSystem.h"
#include "ECS/Component/AlphaFadeTransitionComponent.h"

class AlphaFadeTransitionSystem : public ABehaviorSystem
{
public:
	AlphaFadeTransitionSystem();
	~AlphaFadeTransitionSystem() override;
	
	MAKE_SYSTEM(AlphaFadeTransitionSystem,
         Behavior,
      AlphaFadeTransitionComponent,
   m_AlphaFadeComponentList)

    void Update(float deltaTime) override;

private:
	List<AlphaFadeTransitionComponent*> m_AlphaFadeComponentList;
};
