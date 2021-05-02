#pragma once
#include "Component/Behavior/GravityComponent.h"

#include "Core/SystemManagement/ABehaviorSystem.h"

class GravitySystem final : public ABehaviorSystem
{
public:
	GravitySystem();
	~GravitySystem() override;

	MAKE_SYSTEM(GravitySystem,
			 Behavior,
		  GravityComponent,
	   m_GravityComponentList)

	void Update(float deltaTime) override;

private:
	List<GravityComponent*> m_GravityComponentList;
};