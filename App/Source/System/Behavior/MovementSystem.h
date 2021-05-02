#pragma once
#include "Component/Behavior/MovementComponent.h"

#include "Core/SystemManagement/ABehaviorSystem.h"


class MovementSystem final: public ABehaviorSystem
{
public:
	MovementSystem();
	~MovementSystem() override;

	MAKE_SYSTEM(MovementSystem,
             Behavior,
          MovementComponent,
       m_MovementComponentList)
	
	void Update(float deltaTime) override;
private:
	List<MovementComponent*> m_MovementComponentList;
};