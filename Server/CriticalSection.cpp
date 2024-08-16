#include "CriticalSection.h"


CriticalSection::CriticalSection()
{
	if (InitializeCriticalSectionAndSpinCount(&m_cs, 4000) == false)
	{
		//GetLastError 로 에러 확인 및 처리 하는 로직이 들어가야 한다.
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