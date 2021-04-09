#include "pch.h"
#include "LoadTextureAction.h"

#include <iostream>


#include "IETThread.h"
#include "IExecutionEvent.h"
#include "AssetSystem/TextureManager.h"

LoadTextureAction::LoadTextureAction(const int iconID, IExecutionEvent* onFinishedEvent) :
	m_IconID{iconID},
	m_OnFinishedEvent{onFinishedEvent}
{
}

void LoadTextureAction::OnStartTask()
{
	IETThread::Sleep(1000);
	std::cout << "LoadTextureAction has been executed!\n";

	TextureManager::GetInstance()->LoadSingleStreamAsset(m_IconID);
	m_OnFinishedEvent->OnFinishExecution();
}
