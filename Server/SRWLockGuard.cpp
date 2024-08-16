#include "SRWLockGuard.h"

SWRLockShGuard::SWRLockShGuard(SRWLock* ptr)
{
	m_psrw = ptr;
	if (m_psrw)
	{
		m_psrw->Acquire_Shared();
	}
}

SWRLockShGuard::~SWRLockShGuard()
{
	if (m_psrw)
	{
		m_psrw->Release_Shared();
		m_psrw = NULL;
	}
}

SWRLockExGuard::SWRLockExGuard(SRWLock* ptr)
{
	m_psrw = ptr;
	if (m_psrw)
	{
		m_psrw->Acquire_Exclusive();
	}
}

SWRLockExGuard::~SWRLockExGuard()
{
	if (m_psrw)
	{
		m_psrw->Release_Exclusive();
		m_psrw = NULL;
	}
}
