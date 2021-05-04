#include "pch.h"
#include "LoadingScene.h"

#include "AssetManagement/AssetManager.h"
#include "AssetManagement/Font/Font.h"
#include "AssetManagement/Font/Fonts.h"
#include "AssetManagement/Music/Music.h"
#include "AssetManagement/Music/Musics.h"
#include "AssetManagement/Texture/Texture.h"
#include "AssetManagement/Texture/Textures.h"

#include "ECS/Component/SpriteAnimatorComponent.h"
#include "ECS/Component/TransformComponent.h"
#include "ECS/Component/SpriteRendererComponent.h"

#include "Core/BaseRunner.h"

#include "ECS/Entity.h"
#include "ECS/EntityManager.h"
#include "ECS/EntitySystemManager.h"
#include "ECS/Component/ButtonComponent.h"
#include "ECS/Component/LoadingIndicatorComponent.h"
#include "ECS/Component/TextComponent.h"
#include "ECS/System/Behavior/FPSCounterSystem.h"
#include "ECS/System/Behavior/LoadingIndicatorSystem.h"

#include "Utils/TypeAlias.h"
#include "Utils/Debug.h"
#include "SceneManagement/Scene/Scenes.h"

#include "ECS/System/Behavior/SpriteAnimationSystem.h"
#include "ECS/System/Event/ButtonEventSystem.h"
#include "ECS/System/Render/SpriteRendererSystem.h"
#include "ECS/System/Render/TextRenderSystem.h"

#include "SceneManagement/SceneManager.h"

LoadingScene::LoadingScene() :
	AScene{Scenes::LOADING_SCENE}
{
}

LoadingScene::~LoadingScene()
{
}

void LoadingScene::LoadResourcesImpl()
{
	INFO_LOG(SceneSystem, GetName() << " is loading resources!")

	AssetManager::GetInstance().Load<Music>(MusicNames::LOADING_BGM,
                                            MusicFilepaths::LOADING_BGM);

	AssetManager::GetInstance().Load<Font>(FontNames::MAIN,
                                            FontFilepaths::MAIN);

	AssetManager::GetInstance().Load<Texture>(TextureNames::PLAY_BUTTON,
                                            TextureFilepaths::PLAY_BUTTON);

	AssetManager::GetInstance().Load<Texture>(TextureNames::SHIORI_RUN_ANIM,
                                            TextureFilepaths::SHIORI_RUN_ANIM);

	AssetManager::GetInstance().Load<Texture>(TextureNames::SHIORI_STAND,
                                            TextureFilepaths::SHIORI_STAND);

	AssetManager::GetInstance().Load<Texture>(TextureNames::SHIORI_COMIC,
                                            TextureFilepaths::SHIORI_COMIC);

	AssetManager::GetInstance().Load<Texture>(TextureNames::SHIORI_BG,
                                            TextureFilepaths::SHIORI_BG);
}

void LoadingScene::CreateEntities()
{
	auto& bgm = AssetManager::GetInstance().Acquire<Music>(MusicNames::LOADING_BGM);
	bgm.EnableLooping(true);
	bgm.SetVolume(100.0f);
	bgm.Play();

	{
		auto& bg = EntityManager::GetInstance().CreateEntity("Background");
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::SHIORI_BG);
		auto& transform = bg.BindComponent<TransformComponent>();
		
		transform.SetPosition({BaseRunner::WindowSize.Width * 0.50f, BaseRunner::WindowSize.Height * 0.5f});
		transform.SetScale({1.0f, 1.0f});
		
		auto& sprite = bg.BindComponent<SpriteRendererComponent>(texture, transform);

		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(bg);
	}
	
	{
		auto& run = EntityManager::GetInstance().CreateEntity("Run");
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::SHIORI_RUN_ANIM);
		auto& transform = run.BindComponent<TransformComponent>();
		
		transform.SetPosition({BaseRunner::WindowSize.Width * 0.70f, BaseRunner::WindowSize.Height * 0.915f});
		transform.SetScale({0.35f, 0.35f});
		
		auto& sprite = run.BindComponent<SpriteRendererComponent>(texture, transform);
		sprite.SetOrigin({480.0f / 2, 480.0f / 2});

		run.BindComponent<SpriteAnimatorComponent>(sprite,
													  sf::Vector2i(480, 480),
													  5, 7,
													  0.015f);
		
		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(run);
		EntitySystemManager::GetInstance().MarkEntity<SpriteAnimationSystem>(run);
	}

	{
		auto& stand = EntityManager::GetInstance().CreateEntity("Stand");
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::SHIORI_STAND);
		auto& transform = stand.BindComponent<TransformComponent>();
		
		transform.SetPosition({BaseRunner::WindowSize.Width * 0.24f, BaseRunner::WindowSize.Height * 0.57f});
		transform.SetScale({0.8f, 0.8f});
		
		auto& sprite = stand.BindComponent<SpriteRendererComponent>(texture, transform);

		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(stand);
	}

	{
		auto& comic = EntityManager::GetInstance().CreateEntity("Comic");
		
		auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::SHIORI_COMIC);
		auto& transform = comic.BindComponent<TransformComponent>();
		
		transform.SetPosition({BaseRunner::WindowSize.Width * 0.75f, BaseRunner::WindowSize.Height * 0.4f});
		transform.SetScale({1.0f, 1.0f});
		
		auto& sprite = comic.BindComponent<SpriteRendererComponent>(texture, transform);

		EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(comic);
	}

	auto& fpsCounter = EntityManager::GetInstance().CreateEntity("FPSCounter");
	{
		auto& font = AssetManager::GetInstance().Acquire<Font>(FontNames::MAIN);
		auto& transform = fpsCounter.BindComponent<TransformComponent>();
		auto& textComponent = fpsCounter.BindComponent<TextComponent>(transform, font, 48);
		textComponent.SetColor(sf::Color::Yellow);

		auto& counter = fpsCounter.BindComponent<FPSCounterComponent>(textComponent);
		EntitySystemManager::GetInstance().MarkEntity<TextRenderSystem>(fpsCounter);
		EntitySystemManager::GetInstance().MarkEntity<FPSCounterSystem>(fpsCounter);
	}

	auto& loadingIndicator = EntityManager::GetInstance().CreateEntity("LoadingIndicator");
	{
		auto& font = AssetManager::GetInstance().Acquire<Font>(FontNames::MAIN);
		auto& transform = loadingIndicator.BindComponent<TransformComponent>();
		auto& textComponent = loadingIndicator.BindComponent<TextComponent>(transform, font, 48);
		transform.SetPosition({BaseRunner::WindowSize.Width * 0.75f, BaseRunner::WindowSize.Height * 0.90f});

		auto& loadingComponent = loadingIndicator.BindComponent<LoadingIndicatorComponent>(textComponent,
																							[]() -> void
																							{
																								auto& proceedButton = EntityManager::GetInstance().CreateEntity("ProceedButton");
																							    {
																							        auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::PLAY_BUTTON);
																							        auto& transform = proceedButton.BindComponent<TransformComponent>();

																							        auto& sprite = proceedButton.BindComponent<SpriteRendererComponent>(texture, transform);
																							        transform.SetPosition({BaseRunner::WindowSize.Width * 0.95f, BaseRunner::WindowSize.Height * 0.92f});
																							        transform.SetScale({0.5f, 0.5f});

																							        proceedButton.BindComponent<ButtonComponent>(transform,
																							                                                     sf::Vector2f{128.0f, 128.0f},
																							                                                     []
																							                                                     {
																							                                                         SceneManager::GetInstance().UnloadActiveScenes();
																							                                                         SceneManager::GetInstance().LoadScenes({Scenes::MAIN_SCENE});
																							                                                     });

																							        EntitySystemManager::GetInstance().MarkEntity<ButtonEventSystem>(proceedButton);
																							        EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(proceedButton);
																							    }
																							});

		EntitySystemManager::GetInstance().MarkEntity<TextRenderSystem>(loadingIndicator);
		EntitySystemManager::GetInstance().MarkEntity<LoadingIndicatorSystem>(loadingIndicator);
	}
}

void LoadingScene::Initialize()
{
	INFO_LOG(SceneSystem, GetName() << " is initializing!")
	SceneManager::GetInstance().PreloadSceneResources({Scenes::MAIN_SCENE});
}

void LoadingScene::DestroyEntities()
{
	auto* proceedButton = EntityManager::GetInstance().FindEntityByName("ProceedButton");
	EntityManager::GetInstance().DestroyEntity(*proceedButton);

	auto* loadingIndicator = EntityManager::GetInstance().FindEntityByName("LoadingIndicator");
	EntityManager::GetInstance().DestroyEntity(*loadingIndicator);

	auto* fpsCounter = EntityManager::GetInstance().FindEntityByName("FPSCounter");
	EntityManager::GetInstance().DestroyEntity(*fpsCounter);
}

void LoadingScene::UnloadResources()
{
	INFO_LOG(SceneSystem, GetName() << " is unloading resources!")

	AssetManager::GetInstance().Unload<Music>(MusicNames::LOADING_BGM);
}

void LoadingScene::Deinitialize()
{
}
