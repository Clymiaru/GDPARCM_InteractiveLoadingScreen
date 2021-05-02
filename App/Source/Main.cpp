#include "pch.h"
#include "Core/BaseRunner.h"

#include "Core/SceneManagement/SceneManager.h"
#include "Scene/Scenes.h"
#include "Scene/LoadingScene.h"
#include "Scene/MainScene.h"

int main(const int argc,
          const char** argv)
{
	auto app = BaseRunner({1280, 720},
						  "Interactive Loading Screen",
						  {new LoadingScene(), new MainScene()},
						  Scenes::LOADING_SCENE);

	app.Run();
}
