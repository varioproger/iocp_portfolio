#pragma once
#include<WinSock2.h>
#include<memory>
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
	WSAOVERLAPPED m_overlapped;
	ECIoType m_type;
	WSABUF m_wbuf;
	char* m_buf;
};