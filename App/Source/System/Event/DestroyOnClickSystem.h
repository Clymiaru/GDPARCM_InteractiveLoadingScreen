#pragma once
#include "Component/Behavior/DestroyOnClickComponent.h"
#include "Core/EventSystem/Event.h"
#include "Core/SystemManagement/AEventSystem.h"

class DestroyOnClickSystem final : public AEventSystem
{
public:
	DestroyOnClickSystem();
	~DestroyOnClickSystem() override;
	
	MAKE_SYSTEM(DestroyOnClickSystem,
             Event,
          DestroyOnClickComponent,
       m_DestroyOnClickComponentList)

	void ProcessEvent(Event& event) override;

private:
	List<DestroyOnClickComponent*> m_DestroyOnClickComponentList;
};