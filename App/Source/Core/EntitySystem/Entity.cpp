#include "pch.h"
#include "Entity.h"

#include "EntityManager.h"
#include "AComponent.h"

Entity::Entity(StringRef name) :
	m_Name{name}
{
}

Entity* Entity::Clone(StringRef newEntityName)
{
	auto& entity = EntityManager::GetInstance().CreateEntity(newEntityName);
	for (auto* component : m_ComponentList)
	{
		auto* newComponent = component->Clone(entity);
		entity.m_ComponentList.push_back(newComponent);
		entity.m_ComponentTable[component->GetName()] = newComponent; 
	}
	return &entity;
}

StringRef Entity::GetName() const
{
	return m_Name;
}

void Entity::SetName(StringRef name)
{
	m_Name = name;
}