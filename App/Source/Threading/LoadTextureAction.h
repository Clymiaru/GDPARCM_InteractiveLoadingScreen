#pragma once
#include "IWorkerAction.h"

class IExecutionEvent;

class LoadTextureAction final : public IWorkerAction
{
public:
	explicit LoadTextureAction(int iconID, IExecutionEvent* onFinishedEvent);
	~LoadTextureAction() = default;
	void OnStartTask() override;
private:
	int m_IconID;
	IExecutionEvent* m_OnFinishedEvent;
};
