#pragma once
#include<WRecv.h>
#include"WSend.h"

class Conn
{
public:
	Conn(SOCKET sock);
	~Conn();
public:
	SOCKET m_sock;
	WRecv m_WSARecv;//WSARecv �� ������ Ŭ����
	WSend m_WSASend;//WSASend �� ������ Ŭ����
};

