#include "pch.h"
#include "Core/BaseRunner.h"

#include "SceneManagement/Scene/Scenes.h"
#include "SceneManagement/Scene/LoadingScene.h"
#include "SceneManagement/Scene/MainScene.h"

#include "Threading/ThreadPoolManager.h"

int main(const int argc,
         const char** argv)
{

	ThreadPoolManager::GetInstance().StartThreadPool("AssetThreadPool", 5);
	
	auto app = BaseRunner({1920 - 160, 1080 - 160},
						  "Interactive Loading Screen",
						  {new LoadingScene(), new MainScene()},
						  Scenes::LOADING_SCENE);

	app.Run();
}
