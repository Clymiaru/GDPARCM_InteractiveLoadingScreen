#pragma once
#include "IETThread.h"

class IFinishedTask;
class IWorkerAction;

class PoolWorkerThread final : public IETThread
{
public:
	PoolWorkerThread(int id,
	                 IFinishedTask* finishedTask);

	int GetThreadID() const;

	void ScheduleAction(IWorkerAction* workerAction);

private:
	void Run() override;

	int m_ID;
	IWorkerAction* m_CurrentAction;
	IFinishedTask* m_OnFinishTask;
};
