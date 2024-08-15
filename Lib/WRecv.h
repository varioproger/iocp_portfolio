#pragma once
#include"GlobalDef.h"

class WRecv
{
public:
	WRecv();
	~WRecv();
	BOOL SetBuf(char* _Ptr);
	BOOL SetOverlapped(PVOID _Ptr);
	BOOL SetSocket(SOCKET _Sock);
	BOOL Recv();
	ECSocketResult CompleteRecv(int _Bytes);
	void Clear();
	char* GetBuf();
private:
	BOOL Recv(char* _Buf, int _Len);
private:
	int PacketSize;
	int RecvBytes;
	char* Buf;
	WSAOverLapped_EX Over;
	WSABUF WBuf;
	SOCKET Sock;
};

