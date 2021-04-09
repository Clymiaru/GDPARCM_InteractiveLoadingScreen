#include "pch.h"
#include "AGameObject.h"

AGameObject::AGameObject(String name) :
	m_Name{std::move(name)},
	m_Sprite{nullptr},
	m_Texture{nullptr},
	m_Position{sf::Vector2f(0.0f, 0.0f)},
	m_Scale{sf::Vector2f(1.0f, 1.0f)}
{
}

AGameObject::~AGameObject()
{
	delete m_Sprite;
	delete m_Texture;
}

const String& AGameObject::GetName() const
{
	return m_Name;
}

void AGameObject::Draw(sf::RenderWindow* targetWindow)
{
	if (m_Sprite != nullptr && m_Texture != nullptr)
	{
		m_Sprite->setPosition(m_Position);
		m_Sprite->setScale(m_Scale);
		targetWindow->draw(*m_Sprite);
	}
}

//must be called after being registered to the game object manager or one of the parent game objects
void AGameObject::SetPosition(const float x,
                              const float y)
{
	m_Position.x = x;
	m_Position.y = y;

	if (m_Sprite != nullptr)
	{
		m_Sprite->setPosition(m_Position);
	}
}

void AGameObject::SetScale(const float x,
                           const float y)
{
	m_Scale.x = x;
	m_Scale.y = y;

	if (m_Sprite != nullptr)
	{
		m_Sprite->setScale(m_Scale);
	}
}

const sf::Vector2f& AGameObject::GetPosition() const
{
	return m_Sprite->getPosition();
}

const sf::Vector2f& AGameObject::GetScale() const
{
	return m_Sprite->getScale();
}

const sf::FloatRect AGameObject::GetLocalBounds() const
{
	return m_Sprite->getLocalBounds();
}
