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
	// ��� ��ġ�� ������� ���� ���� Server_IOCP�� Ŀ�� ��ü�� ����
	// �� ������ ���ڰ��� ���� ���� ������ ������ ���� ���ϴµ�, 
	// ���⿡ 0�� �����ϸ� CPU ����ŭ ���� ���డ���� ������ ���� �����Ѵ�.
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