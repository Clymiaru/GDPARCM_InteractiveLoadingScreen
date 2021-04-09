#include "pch.h"
#include "BGObject.h"
#include <iostream>
#include "Core/BaseRunner.h"
#include "AssetSystem/TextureManager.h"

BGObject::BGObject(const String& name) :
	AGameObject(name)
{
}

void BGObject::Initialize()
{
	std::cout << "Declared as " << GetName() << "\n";

	//assign texture
	m_Sprite = new sf::Sprite();

	auto* texture = TextureManager::GetInstance()->GetFromTextureMap("Desert", 0);
	texture->setRepeated(true);
	m_Sprite->setTexture(*texture);
	m_Texture        = texture;
	auto textureSize = m_Sprite->getTexture()->getSize();
	//make BG height x k to emulate repeating BG.
	m_Sprite->setTextureRect(sf::IntRect(0, 0, BaseRunner::WindowSize.Width, BaseRunner::WindowSize.Height * 8));
	SetPosition(0, -BaseRunner::WindowSize.Height * 7);
}

void BGObject::ProcessInput(sf::Event event)
{
}

void BGObject::Update(float deltaTime)
{
	//make BG scroll slowly
	auto position = GetPosition();
	position.y += SPEED_MULTIPLIER * deltaTime;
	SetPosition(position.x, position.y);

	const auto localPos = m_Sprite->getPosition();
	if (localPos.y * deltaTime > 0)
	{
		//reset position
		SetPosition(0, -BaseRunner::WindowSize.Height * 7);
	}
}
