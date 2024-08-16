#pragma once
#include<GlobalDef.h>
#include"ServerGlobalDef.h"
#include"SRWLock.h"
class Conn
{
public:
	Conn(SOCKET sock);
	~Conn();
public:
	SRWLock& GetLock();
	SOCKET GetSocket();
	//int GetPacketRecvSize();
	//void SetPacketRecvSize();
	//void ResetPacketRecvSize();

	//int GetRecvBytes();
	//void SetRecvBytes();
	//void ResetRecvBytes();

	//char* GetRecvBuf();
	//void SetRecvBuf();
	//void ResetRecvBuf();

	//int GetPacketSendBytes();
	//void SetPacketSendBytes();
	//void ResetPacketSendBytes();

	//int GetSendBytes();
	//void SetSendBytes();
	//void ResetSendBytes();

	//int GetSendvBuf();
	//void SetSendvBuf();
	//void ResetSendvBuf();
	BOOL StartRecv();
	BOOL StartSend(char* buf, int size);
private:
	BOOL Recv(char* buf, int len);
	BOOL Send(char* buf, int len);
private:
	SOCKET m_sock;

	int m_packet_recv_size;
	int m_recv_bytes;
	char m_recv_buf[KB_4];
	
	int m_packet_send_size;
	int m_send_bytes;
	char m_send_buf[KB_1];
	WSAOverLapped_EX m_over;

	WSABUF m_wbuf;

	SRWLock m_lock;
};

