#include "pch.h"
#include "IconObject.h"
#include <iostream>
#include "Core/BaseRunner.h"
#include "AssetSystem/TextureManager.h"

IconObject::IconObject(const String& name,
                       int textureIndex):
	AGameObject(name),
	m_TextureIndex{textureIndex}
{
}

void IconObject::Initialize()
{
	//assign texture
	m_Sprite      = new sf::Sprite();
	auto* texture = TextureManager::GetInstance()->GetStreamTextureFromList(m_TextureIndex);
	m_Sprite->setTexture(*texture);
	m_Texture = texture;
}

void IconObject::ProcessInput(sf::Event event)
{
}

void IconObject::Update(float deltaTime)
{
}
