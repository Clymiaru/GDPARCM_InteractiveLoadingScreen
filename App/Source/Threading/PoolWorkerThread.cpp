#include "pch.h"
#include "PoolWorkerThread.h"

#include "IFinishedTask.h"
#include "IWorkerAction.h"

PoolWorkerThread::PoolWorkerThread(const int id,
                                   IFinishedTask* finishedTask) :
	m_ID{id},
	m_CurrentAction{nullptr},
	m_OnFinishTask{finishedTask}
{
}

int PoolWorkerThread::GetThreadID() const
{
	return m_ID;
}

void PoolWorkerThread::ScheduleAction(IWorkerAction* workerAction)
{
	m_CurrentAction = workerAction;
}

void PoolWorkerThread::Run()
{
	if (m_CurrentAction != nullptr)
	{
		m_CurrentAction->OnStartTask();
		m_OnFinishTask->OnFinished(m_ID);
	}
}
