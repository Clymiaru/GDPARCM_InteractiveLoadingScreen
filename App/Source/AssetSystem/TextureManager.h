#pragma once
#include <unordered_map>

#include "Threading/IExecutionEvent.h"
#include "Utils/TypeAlias.h"
#include "SFML/Graphics.hpp"

class TextureManager
{
public:
	static TextureManager* GetInstance();

	void LoadFromAssetList(); //loading of all assets needed for startup
	void LoadSingleStreamAsset(int index);

	//loads a single streaming asset based on index in directory
	sf::Texture* GetFromTextureMap(String assetName,
	                               int frameIndex);

	int GetNumFrames(String assetName);

	sf::Texture* GetStreamTextureFromList(int index);

	int GetNumLoadedStreamTextures() const;

	void InstantiateAsTexture(String path,
	                          String assetName,
	                          bool isStreaming);

private:
	TextureManager();

	TextureManager(TextureManager const&)
	{
	}; // copy constructor is private
	TextureManager& operator=(TextureManager const&)
	{
	}; // assignment operator is private
	static TextureManager* m_SharedInstance;

	HashTable<String, List<sf::Texture*>> m_TextureMap;
	List<sf::Texture*> m_BaseTextureList;
	List<sf::Texture*> m_StreamTextureList;

	const String STREAMING_PATH = "Media/Streaming/";
	int m_StreamingAssetCount   = 0;

	void CountStreamingAssets();
};
