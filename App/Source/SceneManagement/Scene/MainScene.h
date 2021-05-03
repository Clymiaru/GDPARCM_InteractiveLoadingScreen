#pragma once
#include "SceneManagement/AScene.h"

class MainScene final : public AScene
{
public:
	MainScene(const MainScene& other)                        = delete;
	MainScene(MainScene&& other) noexcept                    = delete;
	auto operator=(const MainScene& other) -> MainScene&     = delete;
	auto operator=(MainScene&& other) noexcept -> MainScene& = delete;
	
	explicit MainScene();
	~MainScene() override;
	
	void LoadResources() override;
	void CreateEntities() override;
	void Initialize() override;
	void UnloadResources() override;
	void Deinitialize() override;

};
