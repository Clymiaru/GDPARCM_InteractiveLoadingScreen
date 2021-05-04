#pragma once
#include <mutex>

#include "Threading/IWorkerAction.h"
#include "Threading/Thread.h"
#include "AssetManagement/Asset.h"

#include "Utils/Random.h"
using AssetTable = HashTable<String, Asset*>;
// WorkerAction here is an action of a single load asset routine

template <typename Resource>
class LoadAssetAction final: public IWorkerAction
{
public:
	LoadAssetAction(StringRef name,
					StringRef filepath,
					HashTable<CString, HashTable<String, Asset*>>& assetStorage,
					Uint64& currentlyAsyncAssetsLoaded,
					Uint64& maxAsyncAssetsLoaded,
					std::mutex* assetStorageMutex);

	~LoadAssetAction();

	void OnExecuteAction() override;
private:
	String m_AssetName;
	String m_AssetFilepath;
	HashTable<CString, HashTable<String, Asset*>>& m_AssetStorage;
	Uint64& m_CurrentlyAsyncLoadedAssets;
	Uint64& m_MaxAsyncLoadedAssets;
	std::mutex* m_AssetStorageMutex;
};

template <typename Resource>
LoadAssetAction<Resource>::LoadAssetAction(StringRef name,
										   StringRef filepath,
										   HashTable<CString, HashTable<String, Asset*>>& assetStorage,
										   Uint64& currentlyAsyncAssetsLoaded,
										   Uint64& maxAsyncAssetsLoaded,
										   std::mutex* assetStorageMutex) :
	m_AssetName{name},
	m_AssetFilepath{filepath},
	m_AssetStorage{assetStorage},
	m_CurrentlyAsyncLoadedAssets{currentlyAsyncAssetsLoaded},
	m_MaxAsyncLoadedAssets{maxAsyncAssetsLoaded},
	m_AssetStorageMutex{assetStorageMutex}
{
}

template <typename Resource>
LoadAssetAction<Resource>::~LoadAssetAction()
{
}

template <typename Resource>
void LoadAssetAction<Resource>::OnExecuteAction()
{
	m_AssetStorageMutex->lock();
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticTag()];
	m_MaxAsyncLoadedAssets++;
	m_AssetStorageMutex->unlock();

	Thread::Sleep(Utils::Random::GetFloat(3.0f, 15.0f));
	Resource* resource = new Resource(m_AssetName, m_AssetFilepath);
	Thread::Sleep(Utils::Random::GetFloat(2.0f, 18.0f));
	INFO_LOG(LoadAssetAction, "Asset " << m_AssetName << " is loaded!");
	
	m_AssetStorageMutex->lock();
	selectedAssetStorage[m_AssetName] = resource;
	m_CurrentlyAsyncLoadedAssets++;
	m_AssetStorageMutex->unlock();
}
