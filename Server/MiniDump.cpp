
#include <Windows.h>
#include<stdio.h>
#include <time.h>
#include "MiniDump.h"
#include <assert.h>

Mini_Dump	*Mini_Dump::gpDumper = NULL;

//	Ŭ���� ���� �Լ�
Mini_Dump::Mini_Dump( void )
{
	assert(!gpDumper); // assert�� ���ǽ��� ������ ��� ���α׷� ���� ���� ���α׷��� �ߴ�
	if(!gpDumper)
	{
		// ���ø����̼��� ���μ����� �� �����忡 ���� �ֻ��� ���� ó���⸦ ��ü�ϵ��� �����մϴ�
		//  [in] LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter
		::SetUnhandledExceptionFilter(Handler);
		gpDumper = this;
	}
}

//	������ �ڵ�
//  LPEXCEPTION_POINTERS ������ ���� �Ű� ������ ����ϰ� WINAPI ȣ�� ��Ģ�� ������ LONG ������ ���� ��ȯ�մϴ�.
LONG Mini_Dump::Handler(_EXCEPTION_POINTERS *pExceptionInfo)
{
	// EXCEPTION_CONTINUE_SEARCH : SetErrorMode �÷��׸� �ؼ��ϰų� ���ø����̼� ���� �˾� �޽��� ���ڸ� ȣ���մϴ�.
	LONG	retvel = EXCEPTION_CONTINUE_SEARCH;
	//	���� Ȯ��
	if(!gpDumper)
	{
		return retvel;
	}
	//	���� ����
	return gpDumper->WriteMiniDump(pExceptionInfo);
}


////	������ �����Ѵ�.
LONG Mini_Dump::WriteMiniDump(_EXCEPTION_POINTERS *pExceptionInfo)
{
	// EXCEPTION_CONTINUE_SEARCH : SetErrorMode �÷��׸� �ؼ��ϰų� ���ø����̼� ���� �˾� �޽��� ���ڸ� ȣ���մϴ�.
	LONG	retvel = EXCEPTION_CONTINUE_SEARCH;
	//	�ͼ��� ������ ����
	m_pExceptionInfo = pExceptionInfo;
	//	dbghelp.dll ã��
	HMODULE	hDll = NULL;
	TCHAR	szDbgHelpPath[_MAX_PATH];
	if(GetModuleFileName(NULL,m_szAppPath,_MAX_PATH)) // ����Ǵ� ���μ����� full path�� �����´�.
	{
		// � ���ڿ����� ���ϴ� ���ڿ��� ã�� ��strchr�� �տ�������, strrchr�� �ڿ������� ã�� �Լ��̴�.
		TCHAR	*pSlash = strrchr(m_szAppPath,'\\');  //�ǵڿ� \\ �κ��� �����.
		if(pSlash)
		{
			strcpy_s(m_szAppBaseName,pSlash +1);
			*(pSlash+1) = 0;
		}
		strcpy_s(szDbgHelpPath,m_szAppPath);
		strcat_s(szDbgHelpPath,"DBGHELP.DLL");

		// ���� ���̺귯���� �������� �ε�
		// MFC ���� AfxLoadLibrary �Ǵ� AfxLoadLibraryEx �� ����մϴ�.
		hDll = ::LoadLibrary(szDbgHelpPath);
	}
	if (hDll == NULL)
	{
		// DLL �ٽ� �ѹ� ã��
		hDll = ::LoadLibrary("DBGHELP.DLL");
	}
	if(hDll)
	{
		/*
		GetProcAddress
		 [in] HMODULE hModule : �Լ� �Ǵ� ������ �����ϴ� DLL ��⿡ ���� �ڵ��Դϴ�
		 [in] LPCSTR  lpProcName : �Լ� �Ǵ� ���� �̸� �Ǵ� �Լ��� ���� ���Դϴ�
		�Լ��� �����ϸ� ��ȯ ���� ������ �Լ� �Ǵ� ������ �ּ��Դϴ�.
		�Լ��� �����ϸ� ��ȯ ���� NULL�Դϴ�. Ȯ�� ���� ������ ���������� GetLastError�� ȣ���մϴ�.
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

		// MiniDumpWriteDump�� typedef�� MINIDUMPWRITEDUMP �� dll�� ��ũ ������
		MINIDUMPWRITEDUMP pMiniDumpWriteDump = (MINIDUMPWRITEDUMP)::GetProcAddress(hDll,"MiniDumpWriteDump");
		if(pMiniDumpWriteDump)
		{
			//	���� ���� �̸� ����
			VSetDumpFileName();
			//	���� ���� ����
			HANDLE	hFile = ::CreateFile(m_szDumpPath,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
			if(hFile != INVALID_HANDLE_VALUE)
			{
				_MINIDUMP_EXCEPTION_INFORMATION	ExInfo;
				ExInfo.ThreadId = ::GetCurrentThreadId();
				ExInfo.ExceptionPointers = pExceptionInfo;
				ExInfo.ClientPointers = NULL;
				//	���� ���
				BOOL	bOK = pMiniDumpWriteDump(GetCurrentProcess(),GetCurrentProcessId(),	hFile,MiniDumpNormal,&ExInfo,VGetUserStreamArray(),NULL);
				if(bOK)
				{
					retvel = EXCEPTION_EXECUTE_HANDLER; // UnhandledExceptionFilter���� ��ȯ�ϰ� ����� ���� ó���⸦ �����մϴ�. �̷� ���� �Ϲ������� ���μ��� ���ᰡ �߻��մϴ�.
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

////	���� ���� ������ Ǯ ��� ����
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
