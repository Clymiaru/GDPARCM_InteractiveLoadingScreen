#pragma once
#include "AssetManagement/AssetManager.h"

#include "Threading/Thread.h"
#include <mutex>

#include "Utils/Random.h"

template <class Asset>
class LoadAssetThread final : public Thread
{
public:
	LoadAssetThread(Uint64 id,
					StringRef assetName,
					StringRef assetFilepath,
					std::mutex& mutex,
					int& loadedAssets);
	~LoadAssetThread();

	void Run() override;

private:
	String m_AssetName;
	String m_AssetFilepath;
	std::mutex& m_Mutex;
	int& m_LoadedAssets;
};

template <class Asset>
LoadAssetThread<Asset>::LoadAssetThread(const Uint64 id,
                                        StringRef assetName,
                                        StringRef assetFilepath,
                                        std::mutex& mutex,
                                        int& loadedAssets) :
	Thread{id},
	m_AssetName{assetName},
	m_AssetFilepath{assetFilepath},
	m_Mutex{mutex},
	m_LoadedAssets{loadedAssets}
{
}

template <class Asset>
LoadAssetThread<Asset>::~LoadAssetThread()
{
}

template <class Asset>
void LoadAssetThread<Asset>::Run()
{
	
#if DEBUG
	const auto seconds = 1.0f;
#else
	const auto seconds = Utils::Random::GetFloat(0.01f, 10.0f);
#endif

	Sleep(seconds);
	
	m_Mutex.lock();
	AssetManager::GetInstance().Load<Asset>(m_AssetName, m_AssetFilepath);
	m_LoadedAssets++;
	m_Mutex.unlock();

	// Update global variable of asset loading completed.
}
