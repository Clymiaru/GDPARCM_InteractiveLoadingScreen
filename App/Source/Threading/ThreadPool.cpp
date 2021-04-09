#include "pch.h"
#include "ThreadPool.h"

#include <iostream>

#include "PoolWorkerThread.h"
ThreadPool::ThreadPool(String name,
                       const int maxWorkers) :
    m_Name{name},
    m_MaxWorkers{maxWorkers}
{
	for (auto i = 0; i < m_MaxWorkers; i++)
	{
		m_InactiveThreadQueue.push(new PoolWorkerThread(i, this));
	}
}

ThreadPool::~ThreadPool()
{
}

void ThreadPool::StartScheduler()
{
	m_IsRunning = true;
	Start();
}

void ThreadPool::StopScheduler()
{
	m_IsRunning = false;
}

void ThreadPool::ScheduleTask(IWorkerAction* scheduledAction)
{
	m_PendingActionQueue.push(scheduledAction);
}

void ThreadPool::Run()
{
	std::cout << "Thread pool running!\n";
	while (m_IsRunning)
	{
		if (!m_PendingActionQueue.empty())
		{
			if (!m_InactiveThreadQueue.empty())
			{
				auto* workerThread = m_InactiveThreadQueue.front();
				m_InactiveThreadQueue.pop();
				m_ActiveThreadMap[workerThread->GetThreadID()] = workerThread;

				workerThread->ScheduleAction(m_PendingActionQueue.front());
				m_PendingActionQueue.pop();
				workerThread->Start();				
			}
		}
	}

	std::cout << "Thread pool end!\n";
}

void ThreadPool::OnFinished(const int threadID)
{
	if (m_ActiveThreadMap[threadID] != nullptr)
	{
		delete m_ActiveThreadMap[threadID];
		m_ActiveThreadMap.erase(threadID);
		m_InactiveThreadQueue.push(new PoolWorkerThread(threadID, this));
	}
}



