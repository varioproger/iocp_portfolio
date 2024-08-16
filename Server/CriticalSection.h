#pragma once
#include<WinSock2.h>

class CriticalSection
{
private:
	CRITICAL_SECTION m_cs;
public:
	CriticalSection();
	~CriticalSection();
	void Enter();
	void Leave();
};