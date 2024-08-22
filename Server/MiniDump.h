#pragma once
#include "dbghelp.h"

class Mini_Dump
{
public:
	Mini_Dump(void);
	static Mini_Dump *gpDumper;

protected:
	static LONG WINAPI Handler(struct _EXCEPTION_POINTERS *pExceptionInfo);

	_EXCEPTION_POINTERS *m_pExceptionInfo;
	TCHAR m_szDumpPath[_MAX_PATH];
	TCHAR m_szAppPath[_MAX_PATH];
	TCHAR m_szAppBaseName[_MAX_PATH];
	LONG  WriteMiniDump(_EXCEPTION_POINTERS *pExceptionInfo);

	void VSetDumpFileName(void);
	MINIDUMP_USER_STREAM_INFORMATION *VGetUserStreamArray() {return NULL;};
	void err_display(const char* msg);
};


typedef BOOL	(WINAPI *MINIDUMPWRITEDUMP)
		(
		HANDLE hProcess,
		DWORD dwPid,
		HANDLE hFile,
		MINIDUMP_TYPE DumpType,
		CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
		CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
		CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam
		);