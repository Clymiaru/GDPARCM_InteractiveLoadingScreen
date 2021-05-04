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
	INFO_LOG(SceneSystem, GetName() << " is loading resources!")

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::TRANSITION_IMAGE,
													TextureFilepaths::TRANSITION_IMAGE);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::MAIN_BACKGROUND,
                                                    TextureFilepaths::MAIN_BACKGROUND);

	AssetManager::GetInstance().LoadAsync<Music>(MusicNames::MAIN_BGM,
                                                MusicFilepaths::MAIN_BGM);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::HIYORI_ICON,
												  TextureFilepaths::HIYORI_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::KYOUKA_ICON,
														TextureFilepaths::HIYORI_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::MIMI_ICON,
												  TextureFilepaths::MIMI_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::MISOGI_ICON,
												  TextureFilepaths::MISOGI_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::RANGER_MAHIRU_ICON,
												  TextureFilepaths::RANGER_MAHIRU_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::RANGER_RIN_ICON,
												  TextureFilepaths::RANGER_RIN_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::REI_ICON,
												  TextureFilepaths::REI_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::RIMA_ICON,
												  TextureFilepaths::RIMA_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::SHIORI_ICON,
												  TextureFilepaths::SHIORI_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::YUI_ICON,
												  TextureFilepaths::YUI_ICON);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::MISOGI_STAND,
												  TextureFilepaths::MISOGI_STAND);

	AssetManager::GetInstance().LoadAsync<Texture>(TextureNames::MIYAKO_STAND,
												  TextureFilepaths::MIYAKO_STAND);
}

void MainScene::CreateEntities()
{
	auto& bgm = AssetManager::GetInstance().Acquire<Music>(MusicNames::MAIN_BGM);
	bgm.EnableLooping(true);
	bgm.SetVolume(100.0f);
	bgm.Play();
	
	{
		auto& mainBackground = EntityManager::GetInstance().CreateEntity("MainScene_MainBackground");
		auto& transform = mainBackground.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});

		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::MAIN_BACKGROUND);
		mainBackground.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(mainBackground);
	}

	// Rectangle Black
	{
		auto& transitionObj = EntityManager::GetInstance().CreateEntity("MainScene_TransitionObj");
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

	{
		auto& hiyoriIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(HIYORI_ICON));
		auto& transform = hiyoriIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::HIYORI_ICON);
		hiyoriIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(hiyoriIcon);
	}

	{
		auto& kyoukaIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(KYOUKA_ICON));
		auto& transform = kyoukaIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::KYOUKA_ICON);
		kyoukaIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(kyoukaIcon);
	}

	{
		auto& mimiIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(MIMI_ICON));
		auto& transform = mimiIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::MIMI_ICON);
		mimiIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(mimiIcon);
	}

	{
		auto& misogiIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(MISOGI_ICON));
		auto& transform = misogiIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::MISOGI_ICON);
		misogiIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(misogiIcon);
	}

	{
		auto& rangerMahiruIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(RANGER_MAHIRU_ICON));
		auto& transform = rangerMahiruIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::RANGER_MAHIRU_ICON);
		rangerMahiruIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(rangerMahiruIcon);
	}

	{
		auto& rangerRinIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(RANGER_RIN_ICON));
		auto& transform = rangerRinIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::RANGER_RIN_ICON);
		rangerRinIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(rangerRinIcon);
	}

	{
		auto& reiIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(REI_ICON));
		auto& transform = reiIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::REI_ICON);
		reiIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(reiIcon);
	}

	{
		auto& rimaIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(RIMA_ICON));
		auto& transform = rimaIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::RIMA_ICON);
		rimaIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(rimaIcon);
	}

	{
		auto& shioriIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(SHIORI_ICON));
		auto& transform = shioriIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::SHIORI_ICON);
		shioriIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(shioriIcon);
	}

	{
		auto& yuiIcon = EntityManager::GetInstance().CreateEntity(STRINGIFY(YUI_ICON));
		auto& transform = yuiIcon.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::YUI_ICON);
		yuiIcon.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(yuiIcon);
	}

	{
		auto& misogiStand = EntityManager::GetInstance().CreateEntity(STRINGIFY(MISOGI_STAND));
		auto& transform = misogiStand.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::MISOGI_STAND);
		misogiStand.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(misogiStand);
	}

	{
		auto& miyakoStand = EntityManager::GetInstance().CreateEntity(STRINGIFY(MIYAKO_STAND));
		auto& transform = miyakoStand.BindComponent<TransformComponent>();
		transform.SetPosition({BaseRunner::WindowSize.Width / 2.0f, BaseRunner::WindowSize.Height / 2.0f});
		transform.SetScale({2.0f, 2.0f});
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::MIYAKO_STAND);
		miyakoStand.BindComponent<SpriteRendererComponent>(texture, transform);
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(miyakoStand);
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
