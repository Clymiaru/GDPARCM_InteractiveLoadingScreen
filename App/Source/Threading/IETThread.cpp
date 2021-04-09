#include "pch.h"
#include "IETThread.h"

#include <iostream>
#include <thread>

IETThread::IETThread()
{
}

IETThread::~IETThread()
{
}

void IETThread::Start()
{
	std::thread(&IETThread::Run, this).detach();
	//detach thread for independent execution. without this, join() function must be called.
}

void IETThread::Sleep(const int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
