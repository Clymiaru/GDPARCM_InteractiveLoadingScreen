#pragma once
#include "Asset.h"
using AssetTable = HashTable<String, Asset*>;

class AssetManager final
{
public:
	AssetManager(const AssetManager& other)                = delete;
	AssetManager(AssetManager&& other) noexcept            = delete;
	AssetManager& operator=(const AssetManager& other)     = delete;
	AssetManager& operator=(AssetManager&& other) noexcept = delete;
	
	static AssetManager& GetInstance();
	~AssetManager();
	
	template <class Resource>
	void Load(StringRef name,
	          StringRef filepath);
	
	template <class Resource>
	void Unload(StringRef name);
	
	template <class Resource>
	Resource& Acquire(StringRef name);
private:
	AssetManager();
	HashTable<AssetTag, AssetTable> m_AssetStorage;
};

template <class Resource>
void AssetManager::Load(StringRef name,
                       StringRef filepath)
{
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticTag()];
	const auto found           = selectedAssetStorage.find(name);
	if (found == selectedAssetStorage.end())
		selectedAssetStorage[name] = new Resource(name, filepath);
	ASSERT(found == selectedAssetStorage.end(),
	       AssetSystem,
	       Resource::GetStaticTag() << " (" << name << ") has already been loaded!")
}

template <class Resource>
void AssetManager::Unload(StringRef name)
{
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticTag()];
	const auto found           = selectedAssetStorage.find(name);
	ASSERT(found != selectedAssetStorage.end(),
	       AssetSystem,
	       "Attempted to delete a non-existent " << Resource::GetStaticTag() << " (" << name << ")!")
	auto* deletedAsset = selectedAssetStorage[name];
	selectedAssetStorage.erase(name);
	delete deletedAsset;
}

template <class Resource>
Resource& AssetManager::Acquire(StringRef name)
{
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticTag()];
	auto* found                = selectedAssetStorage[name];
	ASSERT(found != nullptr,
	       AssetSystem,
	       Resource::GetStaticTag() << " (" << name << ") does not exist!")
	INFO_LOG(AssetSystem,
	         name << " (" << Resource::GetStaticTag() << ") has been acquired.")
	return *static_cast<Resource*>(found);
}