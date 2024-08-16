#pragma once
#include<GlobalDef.h>
#include"ServerGlobalDef.h"
#include"SRWLock.h"


class Conn
{
public:
	WSAOverLapped_EX m_recv_overlapped;
	WSAOverLapped_EX m_send_overlapped;
public:
	Conn(SOCKET sock);
	~Conn();
public:
	SRWLock& GetRecvLock();
	SRWLock& GetSendLock();
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
	SRWLock m_recv_lock;
	SRWLock m_send_lock;
private:

	int m_packet_recv_size;
	int m_recv_bytes;
	
	int m_packet_send_size;
	int m_send_bytes;
};

