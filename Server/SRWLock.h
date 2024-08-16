#pragma once
#include<WinSock2.h>

class SRWLock
{
private:
	SRWLOCK m_lock;
public:
	SRWLock();
	~SRWLock() { ; }
	void Acquire_Shared();
	void Release_Shared();
	void Acquire_Exclusive();
	void Release_Exclusive();
};

