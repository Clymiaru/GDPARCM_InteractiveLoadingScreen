#include "pch.h"
#include "GameObjectManager.h"
#include <iostream>

GameObjectManager* GameObjectManager::m_SharedInstance = nullptr;

GameObjectManager* GameObjectManager::GetInstance()
{
	if (m_SharedInstance == nullptr)
	{
		// initialize
		m_SharedInstance = new GameObjectManager();
	}

	return m_SharedInstance;
}

AGameObject* GameObjectManager::FindObjectByName(const String& name)
{
	if (m_GameObjectMap[name] != NULL)
	{
		return m_GameObjectMap[name];
	}
	std::cout << "Object " << name << " not found!";
	return nullptr;
}

List<AGameObject*> GameObjectManager::GetAllObjects() const
{
	return m_GameObjectList;
}

int GameObjectManager::ActiveObjects() const
{
	return m_GameObjectList.size();
}

void GameObjectManager::ProcessInput(sf::Event event)
{
	for (int i = 0; i < m_GameObjectList.size(); i++)
	{
		m_GameObjectList[i]->ProcessInput(event);
	}
}

void GameObjectManager::Update(float deltaTime)
{
	//std::cout << "Delta time: " << deltaTime.asSeconds() << "\n";
	for (int i = 0; i < m_GameObjectList.size(); i++)
	{
		m_GameObjectList[i]->Update(deltaTime);
	}
}

//draws the object if it contains a sprite
void GameObjectManager::Draw(sf::RenderWindow* window)
{
	for (int i = 0; i < m_GameObjectList.size(); i++)
	{
		m_GameObjectList[i]->Draw(window);
	}
}

void GameObjectManager::AddObject(AGameObject* gameObject)
{
	//also initialize the oject
	m_GameObjectMap[gameObject->GetName()] = gameObject;
	m_GameObjectList.push_back(gameObject);
	m_GameObjectMap[gameObject->GetName()]->Initialize();
}

//also frees up allocation of the object.
void GameObjectManager::DeleteObject(AGameObject* gameObject)
{
	m_GameObjectMap.erase(gameObject->GetName());

	int index = -1;
	for (int i = 0; i < m_GameObjectList.size(); i++)
	{
		if (m_GameObjectList[i] == gameObject)
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		m_GameObjectList.erase(m_GameObjectList.begin() + index);
	}

	delete gameObject;
}

void GameObjectManager::DeleteObjectByName(const String& name)
{
	auto* object = FindObjectByName(name);

	if (object != nullptr)
	{
		DeleteObject(object);
	}
}
