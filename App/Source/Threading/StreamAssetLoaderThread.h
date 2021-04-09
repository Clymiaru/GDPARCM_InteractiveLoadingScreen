#pragma once
#include "IETThread.h"
#include "IExecutionEvent.h"
#include "Utils/TypeAlias.h"

class StreamAssetLoaderThread : public IETThread
{
public:
	StreamAssetLoaderThread(const String& streamAssetPath,
	                        IExecutionEvent* executionEvent);

	~StreamAssetLoaderThread() override;

private:
	void Run() override;

	String m_Path;
	IExecutionEvent* m_ExecutionEvent;
};
