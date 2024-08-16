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
	WRecv m_WSARecv;//WSARecv 를 래핑한 클래스
	WSend m_WSASend;//WSASend 를 래핑한 클래스
};

