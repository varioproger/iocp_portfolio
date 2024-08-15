#pragma once
#include<WinSock2.h>
enum class ECSocketResult
{
	SOC_ERROR = -1,
	FINISHED,
	UNFINISHED
};

enum class ECIoType
{
	IO_RECV,
	IO_SEND
};
struct WSAOverLapped_EX
{
	WSAOVERLAPPED overlapped;
	LPVOID ptr;
	ECIoType type;
};