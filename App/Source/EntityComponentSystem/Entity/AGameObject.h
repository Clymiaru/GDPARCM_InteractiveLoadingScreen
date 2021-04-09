#pragma once
#include <SFML/Graphics.hpp>
#include "Utils/TypeAlias.h"

class AGameObject : sf::NonCopyable
{
public:

	explicit AGameObject(String name);

	virtual ~AGameObject();

	virtual void Initialize() = 0;

	virtual void ProcessInput(sf::Event event) = 0;

	virtual void Update(float deltaTime) = 0;

	virtual void Draw(sf::RenderWindow* targetWindow);

	const String& GetName() const;

	virtual void SetPosition(float x,
	                         float y);

	virtual void SetScale(float x,
	                      float y);

	virtual const sf::FloatRect GetLocalBounds() const;

	virtual const sf::Vector2f& GetPosition() const;

	virtual const sf::Vector2f& GetScale() const;

protected:
	String m_Name;
	sf::Sprite* m_Sprite;
	sf::Texture* m_Texture;
	sf::Vector2f m_Position;
	sf::Vector2f m_Scale;
};
