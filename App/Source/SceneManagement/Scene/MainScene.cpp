#include "pch.h"
#include "MainScene.h"
#include "Scenes.h"

MainScene::MainScene() :
	AScene{Scenes::MAIN_SCENE}
{
}

MainScene::~MainScene()
{
}

void MainScene::LoadResources()
{
	INFO_LOG(SceneSystem, GetName() << " is loading resources!")
}

void MainScene::CreateEntities()
{
}

void MainScene::Initialize()
{
	INFO_LOG(SceneSystem, GetName() << " is initializing!")
}

void MainScene::UnloadResources()
{
	INFO_LOG(SceneSystem, GetName() << " is unloading resources!")
}

void MainScene::Deinitialize()
{
}
