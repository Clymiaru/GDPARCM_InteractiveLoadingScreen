#pragma once
#include "Core/SceneManagement/AScene.h"

class LoadingScene final : public AScene
{
public:
	LoadingScene(const LoadingScene& other)                        = delete;
	LoadingScene(LoadingScene&& other) noexcept                    = delete;
	auto operator=(const LoadingScene& other) -> LoadingScene&     = delete;
	auto operator=(LoadingScene&& other) noexcept -> LoadingScene& = delete;
	
	explicit LoadingScene();
	~LoadingScene() override;
	
	void LoadResources() override;
	void CreateEntities() override;
	void Initialize() override;
	void UnloadResources() override;
	void Deinitialize() override;
};
