
#include <Windows.h>
#include<stdio.h>
#include <time.h>
#include "MiniDump.h"
#include <assert.h>

Mini_Dump	*Mini_Dump::gpDumper = NULL;

//	클래스 생성 함수
Mini_Dump::Mini_Dump( void )
{
	assert(!gpDumper); // assert는 조건식이 거짓일 경우 프로그램 실행 도중 프로그램을 중단
	if(!gpDumper)
	{
		// 애플리케이션이 프로세스의 각 스레드에 대한 최상위 예외 처리기를 대체하도록 설정합니다
		//  [in] LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter
		::SetUnhandledExceptionFilter(Handler);
		gpDumper = this;
	}
}

//	덤저장 핸들
//  LPEXCEPTION_POINTERS 형식의 단일 매개 변수를 사용하고 WINAPI 호출 규칙을 가지며 LONG 형식의 값을 반환합니다.
LONG Mini_Dump::Handler(_EXCEPTION_POINTERS *pExceptionInfo)
{
	// EXCEPTION_CONTINUE_SEARCH : SetErrorMode 플래그를 준수하거나 애플리케이션 오류 팝업 메시지 상자를 호출합니다.
	LONG	retvel = EXCEPTION_CONTINUE_SEARCH;
	//	덤프 확인
	if(!gpDumper)
	{
		return retvel;
	}
	//	텀프 저장
	return gpDumper->WriteMiniDump(pExceptionInfo);
}


////	덤프를 저장한다.
LONG Mini_Dump::WriteMiniDump(_EXCEPTION_POINTERS *pExceptionInfo)
{
	// EXCEPTION_CONTINUE_SEARCH : SetErrorMode 플래그를 준수하거나 애플리케이션 오류 팝업 메시지 상자를 호출합니다.
	LONG	retvel = EXCEPTION_CONTINUE_SEARCH;
	//	익셉션 포인터 저장
	m_pExceptionInfo = pExceptionInfo;
	//	dbghelp.dll 찾기
	HMODULE	hDll = NULL;
	TCHAR	szDbgHelpPath[_MAX_PATH];
	if(GetModuleFileName(NULL,m_szAppPath,_MAX_PATH)) // 싱행되는 프로세스의 full path를 가져온다.
	{
		// 어떤 문자열에서 원하는 문자열을 찾을 때strchr는 앞에서부터, strrchr는 뒤에서부터 찾는 함수이다.
		TCHAR	*pSlash = strrchr(m_szAppPath,'\\');  //맨뒤에 \\ 부분을 떼어낸다.
		if(pSlash)
		{
			strcpy_s(m_szAppBaseName,pSlash +1);
			*(pSlash+1) = 0;
		}
		strcpy_s(szDbgHelpPath,m_szAppPath);
		strcat_s(szDbgHelpPath,"DBGHELP.DLL");

		// 동적 라이브러리를 동적으로 로드
		// MFC 앱은 AfxLoadLibrary 또는 AfxLoadLibraryEx 를 사용합니다.
		hDll = ::LoadLibrary(szDbgHelpPath);
	}
	if (hDll == NULL)
	{
		// DLL 다시 한번 찾기
		hDll = ::LoadLibrary("DBGHELP.DLL");
	}
	if(hDll)
	{
		/*
		GetProcAddress
		 [in] HMODULE hModule : 함수 또는 변수를 포함하는 DLL 모듈에 대한 핸들입니다
		 [in] LPCSTR  lpProcName : 함수 또는 변수 이름 또는 함수의 서수 값입니다
		함수가 성공하면 반환 값은 내보낸 함수 또는 변수의 주소입니다.
		함수가 실패하면 반환 값은 NULL입니다. 확장 오류 정보를 가져오려면 GetLastError를 호출합니다.
		https://learn.microsoft.com/ko-kr/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress

		BOOL MiniDumpWriteDump
		[in] HANDLE                            hProcess,
		[in] DWORD                             ProcessId,
		[in] HANDLE                            hFile,
		[in] MINIDUMP_TYPE                     DumpType,
		[in] PMINIDUMP_EXCEPTION_INFORMATION   ExceptionParam,
		[in] PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
		[in] PMINIDUMP_CALLBACK_INFORMATION    CallbackParam
		https://learn.microsoft.com/ko-kr/windows/win32/api/minidumpapiset/nf-minidumpapiset-minidumpwritedump
		*/

		// MiniDumpWriteDump는 typedef된 MINIDUMPWRITEDUMP 와 dll을 링크 시켜줌
		MINIDUMPWRITEDUMP pMiniDumpWriteDump = (MINIDUMPWRITEDUMP)::GetProcAddress(hDll,"MiniDumpWriteDump");
		if(pMiniDumpWriteDump)
		{
			//	덤프 파일 이름 설정
			VSetDumpFileName();
			//	덤프 파일 저장
			HANDLE	hFile = ::CreateFile(m_szDumpPath,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile != INVALID_HANDLE_VALUE)
			{
				_MINIDUMP_EXCEPTION_INFORMATION	ExInfo;
				ExInfo.ThreadId = ::GetCurrentThreadId();
				ExInfo.ExceptionPointers = pExceptionInfo;
				ExInfo.ClientPointers = NULL;
				//	덤프 기록
				BOOL	bOK = pMiniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(),	hFile,MiniDumpNormal,&ExInfo,VGetUserStreamArray(),NULL);
				if(bOK)
				{
					retvel = EXCEPTION_EXECUTE_HANDLER; // UnhandledExceptionFilter에서 반환하고 연결된 예외 처리기를 실행합니다. 이로 인해 일반적으로 프로세스 종료가 발생합니다.
				}
				::CloseHandle(hFile);
			}
		}
		else
		{
			err_display("MiniDump Error 1");
		}
	}
	else
	{
		err_display("MiniDump Error 2");
	}
	TerminateProcess(GetCurrentProcess(),0);
	return retvel;
}

////	저장 덤프 파일의 풀 경로 설정
void Mini_Dump::VSetDumpFileName()
{
	time_t timer = time(NULL);
	struct tm t;
	errno_t error;
	error = localtime_s(&t ,&timer);
	if(error!=0)
	{
		wsprintf(m_szDumpPath, "%s%s_%d.dmp", m_szAppPath, m_szAppBaseName, timer);
	}
	else
	{
		wsprintf(m_szDumpPath, "%s%s_%4d-%2d-%2d-%2d-%2d-%2d.dmp", m_szAppPath, m_szAppBaseName, t.tm_year + 1900, t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);

	}
	
}

void Mini_Dump::err_display(const char* msg)
{
	char error[128] = { 0, };
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	sprintf_s(error, sizeof(error), "[%s] %s", msg, (char*)lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, error, MB_ICONERROR);

	LocalFree(lpMsgBuf);
}
