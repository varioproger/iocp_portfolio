#pragma once
#pragma comment(lib, "ws2_32")
#include <winsock2.h>

class BaseTCP
{
public: //技泼 何盒
	BaseTCP();
	~BaseTCP();
	BOOL WStartUp();
	BOOL WStartUp(WORD wVersionRequested, LPWSADATA lpWSAData);
	SOCKET CreateSocket(u_int AF = AF_INET, u_int Type = SOCK_STREAM, u_int Protocol = 0);
	BOOL   Bind(SOCKET& Sock, ULONG IP = INADDR_ANY, u_int Port = 9000);
	BOOL   Bind(SOCKET& Sock, SOCKADDR_IN& Addr, ULONG IP = INADDR_ANY, u_int Port = 9000);
	BOOL   Listen(SOCKET& Sock, u_int ListenQueueSize = SOMAXCONN);
	BOOL   Connect(SOCKET& Sock, SOCKADDR_IN& Addr, const char* IP = "127.0.0.1", u_int Port = 9000);
	SOCKET Accept(SOCKET ServerSock, SOCKADDR_IN& clientaddr, int& len);
	BOOL NagleOption(SOCKET _Sock, int option = TRUE);
	void WCleanUp();

public: // 单捞磐 贸府 何盒
	BOOL Recv(SOCKET Sock, char* Buf, int Len, int Flags);
	BOOL Recvn(SOCKET Sock, char* Buf, int Len, int Flags);
	BOOL Send(SOCKET Sock, char* Buf, int Len, int Flags);
private:
	WSADATA wsa;
	BOOL StartFlag;
};
