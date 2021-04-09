#include "pch.h"
#include "TextureManager.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include "Threading/IETThread.h"
#include "Threading/StreamAssetLoaderThread.h"
#include "Utils/StringUtils.h"

//a singleton class
TextureManager* TextureManager::m_SharedInstance = nullptr;

TextureManager* TextureManager::GetInstance()
{
	if (m_SharedInstance == nullptr)
	{
		//initialize
		m_SharedInstance = new TextureManager();
	}

	return m_SharedInstance;
}

TextureManager::TextureManager()
{
	CountStreamingAssets();
}

void TextureManager::LoadFromAssetList()
{
	std::cout << "[TextureManager] Reading from asset list" << std::endl;
	std::ifstream stream("Media/assets.txt");
	String path;

	while (std::getline(stream, path))
	{
		std::vector<String> tokens = StringUtils::split(path, '/');
		String assetName           = StringUtils::split(tokens[tokens.size() - 1], '.')[0];
		InstantiateAsTexture(path, assetName, false);
		std::cout << "[TextureManager] Loaded texture: " << assetName << std::endl;
	}
}

void TextureManager::LoadSingleStreamAsset(const int index)
{
	int fileNum = 0;

	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
	{
		if (index == fileNum)
		{
			const auto path = entry.path().generic_string();
			auto tokens          = StringUtils::split(path, '/');
			const auto assetName = StringUtils::split(tokens.back(), '.')[0];

			TextureManager::GetInstance()->InstantiateAsTexture(path, assetName, true);

			std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;
			break;
		}

		fileNum++;
	}
}

sf::Texture* TextureManager::GetFromTextureMap(const String assetName,
                                               int frameIndex)
{
	if (!m_TextureMap[assetName].empty())
	{
		return m_TextureMap[assetName][frameIndex];
	}
	std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
	return nullptr;
}

int TextureManager::GetNumFrames(const String assetName)
{
	if (!m_TextureMap[assetName].empty())
	{
		return m_TextureMap[assetName].size();
	}
	std::cout << "[TextureManager] No texture found for " << assetName << std::endl;
	return 0;
}

sf::Texture* TextureManager::GetStreamTextureFromList(const int index)
{
	return m_StreamTextureList[index];
}

int TextureManager::GetNumLoadedStreamTextures() const
{
	return m_StreamTextureList.size();
}

void TextureManager::CountStreamingAssets()
{
	m_StreamingAssetCount = 0;
	for (const auto& entry : std::filesystem::directory_iterator(STREAMING_PATH))
	{
		m_StreamingAssetCount++;
	}
	std::cout << "[TextureManager] Number of streaming assets: " << m_StreamingAssetCount << std::endl;
}

void TextureManager::InstantiateAsTexture(String path,
                                          String assetName,
                                          bool isStreaming)
{
	auto* texture = new sf::Texture();
	texture->loadFromFile(path);
	m_TextureMap[assetName].push_back(texture);

	if (isStreaming)
	{
		m_StreamTextureList.push_back(texture);
	}
	else
	{
		m_BaseTextureList.push_back(texture);
	}
}
