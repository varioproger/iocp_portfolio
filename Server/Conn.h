#pragma once
#include<WRecv.h>
#include"WSend.h"

class Conn
{
public:
	Conn();
	~Conn();
public:
	int m_index;
	WRecv m_WSARecv;//WSARecv �� ������ Ŭ����
	WSend m_WSASend;//WSASend �� ������ Ŭ����
};

