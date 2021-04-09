#pragma once

class IExecutionEvent
{
public:
	virtual void OnFinishExecution() = 0;
};
