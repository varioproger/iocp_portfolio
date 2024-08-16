#include "SRWLock.h"

SRWLock::SRWLock()
{
	InitializeSRWLock(&m_lock);
}

void SRWLock::Acquire_Shared()
{
	AcquireSRWLockShared(&m_lock);
}

void SRWLock::Release_Shared()
{
	ReleaseSRWLockShared(&m_lock);
}

void SRWLock::Acquire_Exclusive()
{
	AcquireSRWLockExclusive(&m_lock);
}

void SRWLock::Release_Exclusive()
{
	ReleaseSRWLockExclusive(&m_lock);
}
