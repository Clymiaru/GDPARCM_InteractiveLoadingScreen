#pragma once
#include "ASystem.h"

#include "Core/EventSystem/Event.h"

class AEventSystem : public ASystem
{
public:
	virtual void ProcessEvent(Event& event) = 0;
};