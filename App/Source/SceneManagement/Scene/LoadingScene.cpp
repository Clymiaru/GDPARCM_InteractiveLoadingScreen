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

	AssetManager::GetInstance().Load<Texture>(TextureNames::SHIORI_STAND,
                                            TextureFilepaths::SHIORI_STAND);

	AssetManager::GetInstance().Load<Music>(MusicNames::LOADING_BGM,
                                            MusicFilepaths::LOADING_BGM);

	AssetManager::GetInstance().Load<Font>(FontNames::MAIN,
                                            FontFilepaths::MAIN);

	AssetManager::GetInstance().Load<Texture>(TextureNames::PLAY_BUTTON,
                                            TextureFilepaths::PLAY_BUTTON);
}

void LoadingScene::CreateEntities()
{
	// Characters:
	// - Shiori
	// - Hatsune
	auto& bgm = AssetManager::GetInstance().Acquire<Music>(MusicNames::LOADING_BGM);
	bgm.EnableLooping(true);
	bgm.SetVolume(100.0f);
	bgm.Play();
	
	// auto& shioriRun = EntityManager::GetInstance().CreateEntity("ShioriRun");
	// {
	// 	auto& texture = AssetManager::GetInstance().Acquire<Texture>(TextureNames::SHIORI_STAND);
	// 	auto& transform = shioriRun.BindComponent<TransformComponent>();
	// 	transform.SetPosition({BaseRunner::WindowSize.Width * 0.50f, BaseRunner::WindowSize.Height * 0.50f});
	// 	transform.SetScale({0.5f, 0.5f});
	// 	auto& sprite = shioriRun.BindComponent<SpriteRendererComponent>(texture, transform);
	// 	sprite.SetOrigin({480.0f / 2, 480.0f / 2});
	// 	EntitySystemManager::GetInstance().MarkEntity<SpriteRendererSystem>(shioriRun);
	// }

	// auto& loadingBar = EntityManager::GetInstance().CreateEntity("LoadingBar");
	// {
	// }
	
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

	auto& loadingIndicator = EntityManager::GetInstance().CreateEntity("LoadingIndicator");
	{
		auto& font = AssetManager::GetInstance().Acquire<Font>(FontNames::MAIN);
		auto& transform = loadingIndicator.BindComponent<TransformComponent>();
		auto& textComponent = loadingIndicator.BindComponent<TextComponent>(transform, font, 48);
		transform.SetPosition({200, 200});

		auto& loadingComponent = loadingIndicator.BindComponent<LoadingIndicatorComponent>(textComponent, 2);

		EntitySystemManager::GetInstance().MarkEntity<TextRenderSystem>(loadingIndicator);
		EntitySystemManager::GetInstance().MarkEntity<LoadingIndicatorSystem>(loadingIndicator);
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
	// IF we have time, defer it after a loop has been executed.
	SceneManager::GetInstance().PreloadSceneResources({Scenes::MAIN_SCENE});
}

void LoadingScene::DestroyEntities()
{
	auto* proceedButton = EntityManager::GetInstance().FindEntityByName("ProceedButton");
	EntityManager::GetInstance().DestroyEntity(*proceedButton);

	auto* loadingIndicator = EntityManager::GetInstance().FindEntityByName("LoadingIndicator");
	EntityManager::GetInstance().DestroyEntity(*loadingIndicator);
}

void LoadingScene::UnloadResources()
{
	INFO_LOG(SceneSystem, GetName() << " is unloading resources!")

	AssetManager::GetInstance().Unload<Music>(MusicNames::LOADING_BGM);
}

void LoadingScene::Deinitialize()
{
}
