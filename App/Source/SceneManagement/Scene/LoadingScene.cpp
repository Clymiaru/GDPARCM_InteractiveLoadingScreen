#include "pch.h"
#include "LoadingScene.h"

#include "AssetManagement/AssetManager.h"
#include "AssetManagement/Texture/Texture.h"
#include "AssetManagement/Texture/Textures.h"

#include "Component/Behavior/DestroyOnClickComponent.h"
#include "Component/Behavior/GravityComponent.h"
#include "Component/Behavior/MovementComponent.h"
#include "Component/Behavior/SpriteAnimatorComponent.h"
#include "Component/Data/TransformComponent.h"
#include "Component/Data/VelocityComponent.h"
#include "Component/Render/SpriteRendererComponent.h"

#include "Core/BaseRunner.h"

#include "ECS/Entity.h"
#include "ECS/EntityManager.h"
#include "ECS/EntitySystemManager.h"

#include "Utils/TypeAlias.h"
#include "Utils/Debug.h"
#include "SceneManagement/Scene/Scenes.h"

#include "System/Behavior/SpriteAnimationSystem.h"
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

	AssetManager::GetInstance().Load<Texture>(TextureNames::SHIORI_RUN_ANIM,
                                            TextureFilepaths::SHIORI_RUN_ANIM);
}

void LoadingScene::CreateEntities()
{
	auto& shioriRun = EntityManager::GetInstance().CreateEntity("ShioriRun");
	{
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::SHIORI_RUN_ANIM);
		auto& transform = shioriRun.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width * 0.70f, BaseRunner::WindowSize.Height * 0.87f});
		transform.SetScale({0.5f, 0.5f});
		auto& sprite = shioriRun.BindComponent<SpriteRendererComponent>(texture, transform);
		sprite.SetOrigin({480.0f / 2, 480.0f / 2});
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(shioriRun);

		shioriRun.BindComponent<SpriteAnimatorComponent>(sprite, sf::Vector2i{480, 480}, 1, 35, 0.017f);
		EntitySystemManager::GetInstance().MarkEntity<SpriteAnimationSystem>(shioriRun);
	}

	auto& loadingBar = EntityManager::GetInstance().CreateEntity("LoadingBar");
	{
	}

	auto& fpsCounter = EntityManager::GetInstance().CreateEntity("FPSCounter");
	{
	}

	// Create a loading bar (Slider Component)
	// Create an FPS counter that updates every 0.5s

	// Setup the main scene
	// Setup the threading implementation of loading assets in the background

	// After everything works smoothly with the loading bar,
	//	proceed to replicate the plan for the loading screen
	
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
