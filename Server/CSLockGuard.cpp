#include "CSLockGuard.h"

CSLockGuard::CSLockGuard(CriticalSection* pcs)
{
	m_pcs = pcs;
	if (m_pcs)
	{
		m_pcs->Enter();
	}
}
CSLockGuard::~CSLockGuard()
{
	if (m_pcs)
	{
		m_pcs->Leave();
		m_pcs = NULL;
	}
}