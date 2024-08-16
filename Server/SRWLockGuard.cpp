#include "SRWLockGuard.h"

SRWLockShGuard::SRWLockShGuard(SRWLock* ptr)
{
	m_psrw = ptr;
	if (m_psrw)
	{
		m_psrw->Acquire_Shared();
	}
}

SRWLockShGuard::~SRWLockShGuard()
{
	if (m_psrw)
	{
		m_psrw->Release_Shared();
		m_psrw = NULL;
	}
}

SRWLockExGuard::SRWLockExGuard(SRWLock* ptr)
{
	m_psrw = ptr;
	if (m_psrw)
	{
		m_psrw->Acquire_Exclusive();
	}
}

SRWLockExGuard::~SRWLockExGuard()
{
	if (m_psrw)
	{
		m_psrw->Release_Exclusive();
		m_psrw = NULL;
	}
}
