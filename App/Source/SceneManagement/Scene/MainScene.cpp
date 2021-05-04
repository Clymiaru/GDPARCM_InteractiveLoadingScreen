#include "pch.h"
#include "MainScene.h"
#include "Scenes.h"

#include "AssetManagement/AssetManager.h"
#include "AssetManagement/Music/Music.h"
#include "AssetManagement/Music/Musics.h"
#include "AssetManagement/Texture/Texture.h"
#include "AssetManagement/Texture/Textures.h"

#include "Core/BaseRunner.h"

#include "ECS/EntityManager.h"
#include "ECS/EntitySystemManager.h"
#include "ECS/Component/AlphaFadeTransitionComponent.h"
#include "ECS/Component/SpriteRendererComponent.h"
#include "ECS/Component/TransformComponent.h"
#include "ECS/System/Behavior/AlphaFadeTransitionSystem.h"
#include "ECS/System/Render/SpriteRendererSystem.h"

MainScene::MainScene() :
	AScene{Scenes::MAIN_SCENE}
{
}

MainScene::~MainScene()
{
}

void MainScene::LoadResourcesImpl()
{
	// LoadResources will also be moved to a thread for async operations
	// SO that mutex will have to be used to proceeed to CreateEntities
	// And we'll have a variable for asset loading
	INFO_LOG(SceneSystem, GetName() << " is loading resources!")
	
	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::TRANSITION_IMAGE,
													TextureFilepaths::TRANSITION_IMAGE);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::MAIN_BACKGROUND,
                                                    TextureFilepaths::MAIN_BACKGROUND);

	AssetManager::GetInstance().LoadAsync<Music>(MusicNames::MAIN_BGM,
                                                    MusicFilepaths::MAIN_BGM);
}

void MainScene::CreateEntities()
{
	auto& bgm = AssetManager::GetInstance().Acquire<Music>(MusicNames::MAIN_BGM);
	bgm.EnableLooping(true);
	bgm.SetVolume(100.0f);
	bgm.Play();
	
	auto& mainBackground = EntityManager::GetInstance().CreateEntity("MainScene_MainBackground");
	{
		auto& transform = mainBackground.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::MAIN_BACKGROUND);
		mainBackground.BindComponent<SpriteRendererComponent>(texture, transform);
		
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(mainBackground);
	}

	// Rectangle Black
	auto& transitionObj = EntityManager::GetInstance().CreateEntity("MainScene_TransitionObj");
	{
		auto& transform = transitionObj.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::TRANSITION_IMAGE);
		auto& sprite = transitionObj.BindComponent<SpriteRendererComponent>(texture, transform);

		transitionObj.BindComponent<AlphaFadeTransitionComponent>(sprite, 1.0f, 0.0f, 5.0f,
                                                                  [](float currentTime, float initialValue,
                                                                       float finalValue, float duration)
                                                                  {
                                                                          float deltaValue = finalValue - initialValue; 
                                                                          float ratio = currentTime / duration;
                                                                          return deltaValue * ratio + initialValue;
                                                                  });
		
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(transitionObj);
		EntitySystemManager::GetInstance().MarkEntity<AlphaFadeTransitionSystem>(transitionObj);
	}
}

void MainScene::Initialize()
{
	INFO_LOG(SceneSystem, GetName() << " is initializing!")
}

void MainScene::DestroyEntities()
{
}

void MainScene::UnloadResources()
{
	INFO_LOG(SceneSystem, GetName() << " is unloading resources!")
}

void MainScene::Deinitialize()
{
}
