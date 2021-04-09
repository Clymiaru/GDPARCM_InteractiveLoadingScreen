#include "pch.h"
#include "StreamAssetLoaderThread.h"
#include <iostream>
#include "Utils/StringUtils.h"
#include "AssetSystem/TextureManager.h"

StreamAssetLoaderThread::StreamAssetLoaderThread(const String& streamAssetPath,
                                                 IExecutionEvent* executionEvent) :
	m_Path{streamAssetPath},
	m_ExecutionEvent{std::move(executionEvent)}
{
}

StreamAssetLoaderThread::~StreamAssetLoaderThread()
{
	std::cout << "Stream Asset Loader is destroyed!!\n";
}

void StreamAssetLoaderThread::Run()
{
	auto tokens          = StringUtils::split(m_Path, '/');
	const auto assetName = StringUtils::split(tokens.back(), '.')[0];

	Sleep(100);
	TextureManager::GetInstance()->InstantiateAsTexture(m_Path, assetName, true);

	std::cout << "[TextureManager] Loaded streaming texture: " << assetName << std::endl;

	m_ExecutionEvent->OnFinishExecution();

	delete this;
}
