#pragma once
#include<GlobalDef.h>
#include"ServerGlobalDef.h"
#include"SRWLock.h"
#include<mutex>

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
	std::mutex& GetActionLock();
	SOCKET GetSocket();

	int GetRecvPacketSize();
	void SetRecvPacketSize(int size);
	void ResetRecvPacketSize();

	int GetRecvBytes();
	void AddRecvBytes(int bytes);
	void ResetRecvBytes();

	char* GetRecvBuf();
	void ResetRecvBuf();

	int GetSendPacketSize();
	void SetSendPacketSize(int size);
	void ResetSendPacketSize();

	int GetSendBytes();
	void AddSendBytes(int bytes);
	void ResetSendBytes();

	char* GetSendBuf();
	void ResetSendBuf();

public:
	BOOL StartRecv();
	BOOL StartSend(char* buf, int size);
	BOOL SendLeft();
private:
	BOOL Recv(char* buf, int len);
	BOOL Send(char* buf, int len);
	void ClearRecv();
	void ClearSend();
private:
	SOCKET m_sock;
	SRWLock m_recv_lock;
	SRWLock m_send_lock;
	std::mutex m_action_lock;
private:

	int m_recv_packet_size;
	int m_recv_bytes;
	
	int m_send_packet_size;
	int m_send_bytes;
};

