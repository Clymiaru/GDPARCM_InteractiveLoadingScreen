#pragma once
//singleton class
/* Game object manager contains all of the declared game object classes and calls the update function
 */
#include <SFML/Graphics.hpp>
#include "EntityComponentSystem/Entity/AGameObject.h"
#include "Utils/TypeAlias.h"

class GameObjectManager
{
public:
	static GameObjectManager* GetInstance();

	AGameObject* FindObjectByName(const String& name);

	List<AGameObject*> GetAllObjects() const;

	int ActiveObjects() const;

	void ProcessInput(sf::Event event);

	void Update(float deltaTime);

	void Draw(sf::RenderWindow* window);

	void AddObject(AGameObject* gameObject);

	void DeleteObject(AGameObject* gameObject);

	void DeleteObjectByName(const String& name);

private:
	GameObjectManager()
	{
	};

	GameObjectManager(GameObjectManager const&)
	{
	}; // copy constructor is private
	GameObjectManager& operator=(GameObjectManager const&)
	{
	}; // assignment operator is private
	static GameObjectManager* m_SharedInstance;

	HashTable<String, AGameObject*> m_GameObjectMap;
	List<AGameObject*> m_GameObjectList;
};
