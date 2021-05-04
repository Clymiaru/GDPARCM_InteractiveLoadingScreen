#pragma once
#include "ECS/AEventSystem.h"
#include "ECS/Component/ButtonComponent.h"

class ButtonEventSystem final : public AEventSystem
{
public:
	ButtonEventSystem();
	~ButtonEventSystem() override;

	MAKE_SYSTEM(ButtonEventSystem,
             Event,
          ButtonComponent,
       m_ButtonComponentList)

	void ProcessEvent(Event& event) override;

private:
	List<ButtonComponent*> m_ButtonComponentList;
};
