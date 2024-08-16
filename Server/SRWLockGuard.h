#pragma once
#include"SRWLock.h"

class SWRLockShGuard
{
private:
	SRWLock* m_psrw;
public:
	SWRLockShGuard(SRWLock* psrw);
	~SWRLockShGuard();
};

class SWRLockExGuard
{
private:
	SRWLock* m_psrw;
public:
	SWRLockExGuard(SRWLock* psrw);
	~SWRLockExGuard();
};

