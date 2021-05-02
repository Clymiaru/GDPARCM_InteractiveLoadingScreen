#include "pch.h"
#include "EventBroadcaster.h"

EventBroadcaster& EventBroadcaster::GetInstance()
{
	static EventBroadcaster instance;
	return instance;
}

EventBroadcaster::~EventBroadcaster()
{
}

// void EventBroadcastSystem::Broadcast(const Action& event)
// {
// 	for (auto listener : m_SubscriberMap[event.GetType()])
// 		listener->OnActionTriggered(event);
// }

EventBroadcaster::EventBroadcaster()
{
}
