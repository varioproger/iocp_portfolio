#pragma once
#include"GlobalDef.h"

class WSend
{
public:
	WSend();
	~WSend();
	BOOL SetSocket(SOCKET _Sock);
	BOOL SetOverlapped(PVOID _Ptr);
	BOOL SetBuf(char* _Buf);
	BOOL StartSend(char* _Buf, int _Size);
	ECSocketResult CompleteSend(int _Bytes);
	void Clear();
private:
	BOOL Send();
	BOOL Send(char* _Buf, int _Len);

private:
	int SendBytes;
	int SendSize;
	SOCKET Sock;
	WSAOverLapped_EX Over;
	WSABUF WBuf;
	char* Buf;
};