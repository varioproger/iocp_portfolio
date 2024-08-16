#pragma once
#include"SRWLock.h"

class SRWLockShGuard
{
private:
	SRWLock* m_psrw;
public:
	SRWLockShGuard(SRWLock* psrw);
	~SRWLockShGuard();
};

class SRWLockExGuard
{
private:
	SRWLock* m_psrw;
public:
	SRWLockExGuard(SRWLock* psrw);
	~SRWLockExGuard();
};

