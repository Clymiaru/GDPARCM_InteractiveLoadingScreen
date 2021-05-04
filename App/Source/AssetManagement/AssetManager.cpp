#include "pch.h"
#include "AssetManager.h"



AssetManager& AssetManager::GetInstance()
{
	static AssetManager instance;
	return instance;
}

int AssetManager::GetCurrentLoadedAsyncAssets() const
{
	return m_CurrentlyAsyncLoadedAssets;
}

AssetManager::AssetManager() :
	m_AssetStorage(HashTable<AssetTag, AssetTable>()),
	m_CurrentlyAsyncLoadedAssets{0}
{
}

AssetManager::~AssetManager()
{
	ThreadPoolManager::GetInstance().StopThreadPool("AssetThreadPool");
	m_AssetStorage.clear();
}