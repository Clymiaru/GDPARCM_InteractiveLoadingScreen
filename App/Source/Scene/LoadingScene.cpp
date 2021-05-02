#include "pch.h"
#include "LoadingScene.h"

#include "Core/AssetManagement/AssetManager.h"
#include "Asset/Texture/Texture.h"
#include "Asset/Texture/Textures.h"

#include "Component/Behavior/DestroyOnClickComponent.h"
#include "Component/Behavior/GravityComponent.h"
#include "Component/Behavior/MovementComponent.h"
#include "Component/Data/TransformComponent.h"
#include "Component/Data/VelocityComponent.h"
#include "Component/Render/SpriteRendererComponent.h"

#include "Core/EntitySystem/Entity.h"
#include "Core/EntitySystem/EntityManager.h"
#include "Core/SystemManagement/EntitySystemManager.h"

#include "Utils/TypeAlias.h"
#include "Utils/Debug.h"
#include "Scene/Scenes.h"

#include "System/Behavior/GravitySystem.h"
#include "System/Behavior/MovementSystem.h"
#include "System/Event/DestroyOnClickSystem.h"
#include "System/Render/SpriteRendererSystem.h"

LoadingScene::LoadingScene() :
	AScene{Scenes::LOADING_SCENE}
{
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::LoadResources()
{
	INFO_LOG(SceneSystem, GetName() << " is loading resources!")

	AssetManager::GetInstance().Load<Texture>(TextureNames::TEST_IMAGE_3,
											TextureFilepaths::TEST_IMAGE_3);
}

void LoadingScene::CreateEntities()
{
	auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::TEST_IMAGE_3);

	for (auto i = 0; i < 8; i++)
	{
		auto entityName = String("TestEntity_") + std::to_string(i);
		auto& testEntity = EntityManager::GetInstance().CreateEntity(entityName);
		auto& transform = testEntity.BindComponent<TransformComponent>();
		transform.SetPosition({100.0f + 128.0f * i, 100.0f});
		testEntity.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(testEntity);

		testEntity.BindComponent<DestroyOnClickComponent>(transform);
		EntitySystemManager::GetInstance().MarkEntity<DestroyOnClickSystem>(testEntity);

		auto& velocity = testEntity.BindComponent<VelocityComponent>(sf::Vector2f{160.0f, 0.0f});
		testEntity.BindComponent<MovementComponent>(transform, velocity);
		testEntity.BindComponent<GravityComponent>(transform, 0.098f);
		
		EntitySystemManager::GetInstance().MarkEntity<MovementSystem>(testEntity);
		EntitySystemManager::GetInstance().MarkEntity<GravitySystem>(testEntity);
	}

	/*
		auto& fpsCounter = UIManager::GetInstance().CreateWidget("FPSCounter");
		auto& rect = fpsCounter.BindComponent<RectComponent>();
		auto& text = fpsCounter.BindComponent<TextComponent>(rect);
		fpsCounter.BindComponent<FPSComponent>(); 
		SystemManager::GetInstance().MarkWidget<FPSSystem>();
	 */



	
}

void LoadingScene::Initialize()
{
	INFO_LOG(SceneSystem, GetName() << " is initializing!")
}

void LoadingScene::UnloadResources()
{
	INFO_LOG(SceneSystem, GetName() << " is unloading resources!")
}

void LoadingScene::Deinitialize()
{
}
