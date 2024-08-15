#include "pch.h"
#include "BaseTCP.h"
#include <ws2tcpip.h>
#include"Error0.h"


BaseTCP::BaseTCP()
{
	StartFlag = FALSE;
}
BaseTCP::~BaseTCP()
{
	WCleanUp();
}
BOOL BaseTCP::WStartUp()
{
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return FALSE;
	}
	StartFlag = TRUE;
	return TRUE;
}
BOOL BaseTCP::WStartUp(WORD wVersionRequested, LPWSADATA lpWSAData)
{
	if (WSAStartup(wVersionRequested, lpWSAData) != 0)
	{
		return FALSE;
	}
	StartFlag = TRUE;
	return TRUE;
}
SOCKET BaseTCP::CreateSocket(u_int AF, u_int Type, u_int Protocol)
{
	SOCKET sock = INVALID_SOCKET;
	if (StartFlag)
	{
		if (StartFlag)
		{
			sock = socket(AF, Type, Protocol);
			if (sock == INVALID_SOCKET)
			{
				err_quit("socket()");
			}
		}
		else
		{
			err_display("Need to StartUp First");
		}
	}
	else
	{
		MessageBox(NULL, nullptr, "WStartUp First", MB_ICONERROR);
	}
	return sock;
}
BOOL BaseTCP::Bind(SOCKET& Sock, ULONG IP, u_int Port)
{
	if (StartFlag)
	{
		SOCKADDR_IN Addr;
		ZeroMemory(&Addr, sizeof(Addr));
		Addr.sin_family = AF_INET;
		Addr.sin_addr.s_addr = htonl(IP);
		Addr.sin_port = htons(Port);
		if (bind(Sock, (SOCKADDR*)&Addr, sizeof(Addr)) == SOCKET_ERROR)
		{
			err_quit("bind()");
		}
		return TRUE;
	}
	else
	{
		MessageBox(NULL, nullptr, "WStartUp First", MB_ICONERROR);
	}
	return FALSE;
}
BOOL BaseTCP::Bind(SOCKET& Sock, SOCKADDR_IN& Addr, ULONG IP, u_int Port)
{
	if (StartFlag)
	{
		ZeroMemory(&Addr, sizeof(Addr));
		Addr.sin_family = AF_INET;
		Addr.sin_addr.s_addr = htonl(IP);
		Addr.sin_port = htons(Port);
		if (bind(Sock, (SOCKADDR*)&Addr, sizeof(Addr)) == SOCKET_ERROR)
		{
			err_quit("bind()");
		}
		return TRUE;
	}
	else
	{
		err_display("Need to StartUp First");
	}
	return FALSE;
}
BOOL BaseTCP::Listen(SOCKET& Sock, u_int ListenQueueSize)
{
	if (StartFlag)
	{
		if (listen(Sock, ListenQueueSize) == SOCKET_ERROR)
		{
			err_quit("listen()");
		}
		return TRUE;
	}
	else
	{
		MessageBox(NULL, nullptr, "WStartUp First", MB_ICONERROR);
	}
	return FALSE;
}
BOOL BaseTCP::Connect(SOCKET& Sock, SOCKADDR_IN& Addr, const char* IP, u_int Port)
{
	if (StartFlag)
	{
		ZeroMemory(&Addr, sizeof(Addr));
		Addr.sin_family = AF_INET;
		Addr.sin_port = htons(Port);
		InetPton(AF_INET, IP, &Addr.sin_addr.s_addr);
		if (connect(Sock, (SOCKADDR*)&Addr, sizeof(Addr)) == SOCKET_ERROR)
		{
			err_quit("connect()");
		}
		return TRUE;
	}
	else
	{
		MessageBox(NULL, nullptr, "WStartUp First", MB_ICONERROR);
	}
	return FALSE;
}
SOCKET BaseTCP::Accept(SOCKET ServerSock, SOCKADDR_IN& clientaddr, int& len)
{
	SOCKET client_sock = INVALID_SOCKET;

	int port = 0;
	if (StartFlag)
	{
		len = sizeof(clientaddr);
		client_sock = accept(ServerSock, (SOCKADDR*)&clientaddr, &len);
		if (client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			return INVALID_SOCKET;
		}
	}
	else
	{
		MessageBox(NULL, nullptr, "WStartUp First", MB_ICONERROR);
	}
	return client_sock;
}
BOOL BaseTCP::NagleOption(SOCKET _Sock, int option)
{
	//빠른 반응이 필요한 부분에서는 주로 Nagle알고리즘을 Off시킨다.
	//TRUE : Nagle Off, FALSE : Nagle On
	setsockopt(_Sock,			//소켓    
		IPPROTO_TCP,			//소켓 레벨
		TCP_NODELAY,			//소켓 옵션
		(const char*)&option,	//옵션값의 주소값
		sizeof(option));		//옵션값의 
	return TRUE;
}

void BaseTCP::WCleanUp()
{
	if (StartFlag)
	{
		WSACleanup();
	}
}
BOOL BaseTCP::Recv(SOCKET Sock, char* Buf, int Len, int Flags)
{
	int received = recv(Sock, Buf, Len, Flags);
	if (received == SOCKET_ERROR)
	{
		return SOCKET_ERROR;
	}
	else if (received == 0)
	{
		return FALSE;
	}
	return received;
}
BOOL BaseTCP::Recvn(SOCKET Sock, char* Buf, int Len, int Flags)
{
	int received;
	char* ptr = Buf;
	int left = Len;

	while (left > 0)
	{
		received = recv(Sock, ptr, left, Flags);
		if (received == SOCKET_ERROR)
		{
			return SOCKET_ERROR;
		}
		else if (received == 0)
		{
			break;
		}
		left -= received;
		ptr += received;
	}
	return Len;
}
BOOL BaseTCP::Send(SOCKET Sock, char* Buf, int Len, int Flags)
{
	int retval = send(Sock, Buf, Len, Flags);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
	}
	return retval;
}