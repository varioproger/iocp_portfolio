#pragma once
#include"BaseTCP.h"
#include"GlobalDef.h"
#include<vector>
#include<thread>

class CompletionPort : public BaseTCP
{
public:
	CompletionPort();
	~CompletionPort();
	BOOL CreateIOPort();
	BOOL Register(SOCKET sock, int key);
	void CalculateThreadCount();
	size_t GetThreadCount();
	void PostStopSignal(u_int key = 1);
	void JoinThread();

public:
	template<typename T>
	BOOL BeginThread(size_t MaxThread, std::vector<T> t)
	{
		if (MaxThread > ThreadCount || t.size() != MaxThread)
		{
			return FALSE;
		}
		for (size_t i = 0; i < MaxThread; i++)
		{
			vThread.emplace_back(std::thread(&CompletionPort::WorkerThread, this, &t[i]));
		}
		return TRUE;
	}
public:
	virtual void WorkerThread(LPVOID arg) = 0;
	virtual ECSocketResult CompleteSend(LPVOID conn, int Bytes) = 0;
	virtual ECSocketResult CompleteRecv(LPVOID conn, int Bytes) = 0;
	virtual void CloseCon(LPVOID conn) = 0;
protected:
	int ThreadCount;
	HANDLE hCP;
	std::vector<std::thread> vThread;
};