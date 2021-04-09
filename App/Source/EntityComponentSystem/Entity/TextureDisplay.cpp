#include "pch.h"
#include "TextureDisplay.h"
#include <iostream>

#include "Core/BaseRunner.h"
#include "EntityComponentSystem/GameObjectManager.h"
#include "IconObject.h"
#include "Threading/LoadTextureAction.h"
#include "AssetSystem/TextureManager.h"

TextureDisplay::TextureDisplay():
	AGameObject("TextureDisplay"),
	m_Ticks{0},
	m_HasStartedStreaming{false},
	m_ColumnGrid{0},
	m_RowGrid{0},
	m_IconIndex{0},
	m_IconList{List<IconObject*>()}
{
}

void TextureDisplay::Initialize()
{
	m_ThreadPool->StartScheduler();
}

void TextureDisplay::ProcessInput(sf::Event event)
{
}

void TextureDisplay::Update(float deltaTime)
{
	m_Ticks += deltaTime;
	if (m_Ticks >= STREAMING_LOAD_DELAY &&
		m_StreamingType == StreamingType::SINGLE_STREAM &&
		m_IconIndex < MAX_ICONS)
	{
		m_Ticks = 0;
		m_ThreadPool->ScheduleTask(new LoadTextureAction(m_IconIndex, this));
		std::cout << "Added a task!\n";
	}
}

void TextureDisplay::OnFinishExecution()
{
	SpawnObject();
	m_IconIndex++;

	if (m_IconIndex >= MAX_ICONS)
	{
		m_ThreadPool->StopScheduler();
		std::cout << "Icon Index: " << m_IconIndex << "\n";
	}
}

void TextureDisplay::SpawnObject()
{
	String objectName   = "Icon_" + std::to_string(m_IconList.size());
	IconObject* iconObj = new IconObject(objectName, static_cast<int>(m_IconList.size()));
	m_IconList.push_back(iconObj);

	//set position
	auto IMG_WIDTH = 68;
	auto IMG_HEIGHT = 68;
	auto x= m_ColumnGrid * IMG_WIDTH;
	auto y= m_RowGrid * IMG_HEIGHT;
	iconObj->SetPosition(static_cast<float>(x), static_cast<float>(y));

	// std::cout << "Set position: " << x << " " << y << std::endl;

	m_ColumnGrid++;
	if (m_ColumnGrid >= MAX_COLUMN)
	{
		m_ColumnGrid = 0;
		m_RowGrid++;
	}
	GameObjectManager::GetInstance()->AddObject(iconObj);
}
