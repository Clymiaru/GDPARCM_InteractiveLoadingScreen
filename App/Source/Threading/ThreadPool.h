#pragma once
#include <queue>
#include <unordered_map>
#include "IETThread.h"
#include "IFinishedTask.h"
#include "Utils/TypeAlias.h"

class PoolWorkerThread;
class IWorkerAction;

class ThreadPool final : public IFinishedTask, public IETThread
{
public:
	ThreadPool(String name, int maxWorkers);
	~ThreadPool() override;
	void StartScheduler();
	void StopScheduler();
	void ScheduleTask(IWorkerAction* scheduledAction);

protected:
	void Run() override;
	void OnFinished(int threadID) override;

private:
	String m_Name;
	int m_MaxWorkers;
	bool m_IsRunning = false;

	std::unordered_map<int, PoolWorkerThread*> m_ActiveThreadMap;
	std::queue<PoolWorkerThread*> m_InactiveThreadQueue;
	std::queue<IWorkerAction*> m_PendingActionQueue;
};
