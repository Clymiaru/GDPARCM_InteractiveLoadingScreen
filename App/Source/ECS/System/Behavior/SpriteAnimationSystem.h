#pragma once
#include "ECS/Component/SpriteAnimatorComponent.h"
#include "ECS/ABehaviorSystem.h"

class SpriteAnimationSystem final : public ABehaviorSystem
{
public:
	SpriteAnimationSystem();
	~SpriteAnimationSystem() override;
	
	MAKE_SYSTEM(SpriteAnimationSystem,
             Behavior,
          SpriteAnimatorComponent,
       m_SpriteAnimatorComponentList)

	void Update(float deltaTime) override;

private:
	List<SpriteAnimatorComponent*> m_SpriteAnimatorComponentList;
};
