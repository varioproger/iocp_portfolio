#include "pch.h"
#include "Error0.h"
#include <WinSock2.h>
#include<Windows.h>
#include<stdio.h>
#include <process.h>

void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}


// 소켓 함수 오류 출력
void err_display(const char* msg)
{
	char error[128] = { 0, };
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);

	sprintf_s(error, sizeof(error), "[%s] %s", msg, (char*)lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, error, MB_ICONERROR);

	LocalFree(lpMsgBuf);
}
void err_display(int errcode)
{
	char error[128] = { 0, };
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errcode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	sprintf_s(error, sizeof(error), "[%d] %s", errcode, (char*)lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, error, MB_ICONERROR);
	LocalFree(lpMsgBuf);
}
