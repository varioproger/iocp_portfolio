#pragma once
#include<GlobalDef.h>
#include"../Global/PacketDefinition.h"
#include"ServerGlobalDef.h"
#include"User.h"
#include"Character.h"
#include<mutex>
#include<concurrent_queue.h>
#include<optional>

class Conn
{
public:
	WSAOverLapped_EX m_recv_overlapped;
	WSAOverLapped_EX m_send_overlapped;
public:
	Conn(SOCKET sock);
	~Conn();
public:
	std::mutex& GetRecvLock();
	std::mutex& GetSendLock();
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
	BOOL AddSend(BaseMsg* packet);
	BOOL PopSend();
	BOOL SendLeft();
private:
	BOOL Recv(char* buf, int len);
	BOOL Send(char* buf, int len);
	void ClearRecv();
	void ClearSend();

private:  // 관련 작업 진행해야함
	std::unique_ptr<User> m_user; // 현재 접속 중인 유저
	std::unique_ptr<Character> m_character; // 현재 접속 중인 

private:
	SOCKET m_sock;
	std::mutex m_recv_lock;
	std::mutex m_send_lock;
private:
	int m_recv_packet_size;
	int m_recv_bytes;
	
	int m_send_packet_size;
	int m_send_bytes;
	concurrency::concurrent_queue<BaseMsg*> m_send_queue;
};

