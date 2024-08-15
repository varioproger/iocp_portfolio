#include "pch.h"
#include "CompletionPort.h"

CompletionPort::CompletionPort()
{
	ThreadCount = 0;
	hCP = NULL;
	vThread.clear();
}

CompletionPort::~CompletionPort()
{
	if (vThread.empty() == FALSE)
	{
		JoinThread();
	}
}

BOOL CompletionPort::CreateIOPort()
{
	// 어떠한 장치와 연결되지 않은 순수 Server_IOCP의 커널 객체를 생성
	// 맨 마지막 인자값은 동시 실행 가능한 스레드 수를 뜻하는데, 
	// 여기에 0을 기입하면 CPU 수만큼 동시 실행가능한 스레드 수를 지정한다.
	hCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, ThreadCount);
	if (hCP == NULL)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CompletionPort::Register(SOCKET sock, int key)
{
	CreateIoCompletionPort((HANDLE)sock, hCP, key, 0);
	return TRUE;
}

void CompletionPort::CalculateThreadCount()
{
	SYSTEM_INFO sys;
	GetSystemInfo(&sys);
	ThreadCount = sys.dwNumberOfProcessors;
}

size_t CompletionPort::GetThreadCount()
{
	CalculateThreadCount();
	return ThreadCount;
}

void CompletionPort::PostStopSignal(u_int key)
{
	for (size_t i = 0; i < vThread.size(); i++)
	{
		PostQueuedCompletionStatus(hCP, 0, key, NULL);
	}
}
void CompletionPort::JoinThread()
{
	for (auto& thread : vThread)
	{
		thread.join();
	}
	vThread.clear();
}