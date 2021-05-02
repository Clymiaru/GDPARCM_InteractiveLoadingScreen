#pragma once
#include <functional>
#include "Event.h"
#include "Utils/TypeAlias.h"

class Action final
{
public:
	Action(const int id,
		const std::function<void(const Event& event)>& function) :
		m_ID{id},
		m_Function{function}
	{
	}

	void operator()(const Event& event) const
	{
		m_Function(event);
	}

	bool operator== (const Action& other) const
	{
		return m_ID == other.m_ID;
	}
private:
	int m_ID;
	std::function<void(const Event& event)> m_Function;
	
};

class EventBroadcaster
{
public:
	EventBroadcaster(const EventBroadcaster& other)                = delete;
	EventBroadcaster(EventBroadcaster&& other) noexcept            = delete;
	EventBroadcaster& operator=(const EventBroadcaster& other)     = delete;
	EventBroadcaster& operator=(EventBroadcaster&& other) noexcept = delete;
	static EventBroadcaster& GetInstance();
	~EventBroadcaster();
	// template <EventType eventType>
	// void Subscribe(Action action);
	// template <ActionType actionEventType>
	// void Unsubscribe(IActionListener* listener);
	//void Broadcast(const Action& event);
private:
	EventBroadcaster();
	// HashTable<ActionType, List<IActionListener*>> m_SubscriberMap;
	//HashTable<EventType, List<Action>> m_SubscriberMap;
};

// template <EventType eventType>
// void EventBroadcastSystem::Subscribe(Action action)
// {
// 	auto toSearch              = m_SubscriberMap[eventType];
// 	
// 	const auto foundSubscriber = std::ranges::find(toSearch, action);
// 	
// 	if (foundSubscriber == toSearch.end())
// 	{
// 		m_SubscriberMap[eventType].push_back(action);
// 		return;
// 	}
//
// 	INFO_LOG(EventBroadcasterSystem, "The listener has already subscribed to " << STRINGIFY(actionEventType) << ".");
// }

// template <ActionType actionEventType>
// void EventBroadcastSystem::Subscribe(IActionListener* listener)
// {
// 	auto toSearch              = m_SubscriberMap[actionEventType];
// 	const auto foundSubscriber = std::ranges::find(toSearch, listener);
//
// 	if (foundSubscriber == toSearch.end())
// 	{
// 		m_SubscriberMap[actionEventType].push_back(listener);
// 		return;
// 	}
//
// 	INFO_LOG(EventBroadcasterSystem, "The listener has already subscribed to " << STRINGIFY(actionEventType) << ".");
// }
//
// template <ActionType actionEventType>
// void EventBroadcastSystem::TestSubscribe(std::function<void(const Action&)> action)
// {
// }
//
// template <ActionType actionEventType>
// void EventBroadcastSystem::Unsubscribe(IActionListener* listener)
// {
// 	const auto eventSubscriberList = m_SubscriberMap.find(actionEventType);
//
// 	ASSERT(eventSubscriberList != m_SubscriberMap.end(), EventBroadcasterSystem,
// 	       STRINGIFY(actionEventType) << " has no subscribers!");
//
// 	auto subscriberList = eventSubscriberList->second;
//
// 	subscriberList.erase(std::ranges::remove(subscriberList, listener).begin(), subscriberList.end());
// 	subscriberList.shrink_to_fit();
//
// 	INFO_LOG(EventBroadcasterSystem, "Subscriber has been removed.")
// }

