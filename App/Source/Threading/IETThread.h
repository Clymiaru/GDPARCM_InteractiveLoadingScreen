#pragma once

/// <summary>
/// Representation of a Java/C# like thread class. The behavior must be inherited by a class that needs to be threaded.
/// By: NeilDG
/// </summary>
class IETThread
{
public:
	IETThread();

	virtual ~IETThread();

	void Start(); //schedules thread execution
	static void Sleep(int ms);

protected:
	virtual void Run() = 0;
};
