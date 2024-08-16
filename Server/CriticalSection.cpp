#include "CriticalSection.h"


CriticalSection::CriticalSection()
{
	if (InitializeCriticalSectionAndSpinCount(&m_cs, 4000) == false)
	{
		//GetLastError �� ���� Ȯ�� �� ó�� �ϴ� ������ ���� �Ѵ�.
	}
}
CriticalSection::~CriticalSection()
{
	DeleteCriticalSection(&m_cs);
}

void CriticalSection::Enter()
{
	EnterCriticalSection(&m_cs);
}
void CriticalSection::Leave()
{
	LeaveCriticalSection(&m_cs);
}