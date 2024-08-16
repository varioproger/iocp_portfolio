#pragma once
#include"CriticalSection.h"

class CSLockGuard
{
private:
	CriticalSection* m_pcs;
public:
	CSLockGuard(CriticalSection* pcs);
	~CSLockGuard();

};
